# MPI 点对点通信示例

本项目演示了 MPI（Message Passing Interface）中两种不同的点对点发送模式：
- `MPI_Send`：标准非阻塞发送
- `MPI_Ssend`：同步阻塞发送

## 📋 项目结构

```
23_point_to_point_communication/
├── main.cpp           # 主程序源码
├── CMakeLists.txt     # CMake 构建配置
├── conanfile.txt      # Conan 依赖配置
├── build/             # 构建目录
└── README.md          # 本文档
```

## 🔧 编译和运行

### 编译

```bash
cd build
conan install .. --build=missing
cmake ..
make
```

### 运行

```bash
mpirun -np 4 ./bin/23_point_to_point_communication
```

## 📊 输出示例

程序运行时会展示两种发送模式的区别：

### 1. MPI_Send - 标准非阻塞发送

```
========== send_data (MPI_Send - 非阻塞发送) ==========
Ready to send 0--->1
Data sent 0--->1
Ready to send 0--->2
Data sent 0--->2
Ready to send 0--->3
Data sent 0--->3
Rank 1 received from 0 the value 42
Rank 2 received from 0 the value 42
Rank 3 received from 0 the value 42
```

**特点：**
- Rank 0 可以立即发送消息（可能使用缓冲区）
- "Data sent" 消息出现时，数据可能还未真正到达接收方
- 发送操作可能在接收方调用 `MPI_Recv` 之前就完成
- 性能较高，但需要小心处理缓冲区

### 2. MPI_Ssend - 同步阻塞发送

```
========== 分隔线 ==========

========== ssend_data (MPI_Ssend - 同步阻塞发送) ==========
Ready to send 0--->1
Data sent 0--->1
Ready to send 0--->2
Data sent 0--->2
Ready to send 0--->3
Data sent 0--->3
Rank 1 received from 0 the value 42
Rank 2 received from 0 the value 42
Rank 3 received from 0 the value 42
```

**特点：**
- Rank 0 必须等待接收方开始接收才能继续
- "Data sent" 消息出现时，接收方已经开始接收
- 更安全，保证消息确实被接收
- 性能相对较低，但更可预测

## 🔍 两种发送模式的对比

| 特性 | MPI_Send | MPI_Ssend |
|------|----------|-----------|
| **阻塞性** | 可能非阻塞（取决于缓冲区） | 必须阻塞到接收开始 |
| **完成条件** | 消息已发送（可能在缓冲区） | 接收方已开始接收 |
| **性能** | 较快 | 较慢 |
| **安全性** | 需要注意缓冲区 | 更安全 |
| **使用场景** | 一般通信 | 需要确认的同步场景 |

## 💡 关键技术点

### 1. MPI 生命周期

```cpp
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);        // ⭐ 初始化（只能一次）
    
    // ... MPI 通信代码 ...
    
    MPI_Finalize();                // ⭐ 清理（只能一次）
    return 0;
}
```

**规则：**
- `MPI_Init()` 在整个程序中只能调用一次
- `MPI_Finalize()` 在整个程序中只能调用一次
- 不能在 `MPI_Finalize()` 后再调用 `MPI_Init()`

### 2. 同步输出策略

为了避免多进程输出混乱，采用**统一由 rank 0 输出**的策略：

```cpp
// ✅ 统一输出模式
if(rank == 0) {
    // rank 0 收集所有结果并输出
    for(int i = 1; i < size; ++i) {
        int received_value;
        MPI_Recv(&received_value, 1, MPI_INT, i, tag, 
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received: %d\n", i, received_value);
    }
} else {
    // 其他进程发送结果给 rank 0
    MPI_Send(&value, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
}
```

**优点：**
- 输出顺序可控
- 避免多进程输出竞争
- 适合调试和日志记录

### 3. 标准输出缓冲控制

```cpp
// 关闭标准输出缓冲，强制立即输出
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);
```

**原因：**
- MPI 多进程环境下，标准输出可能被缓冲延迟
- 使用 `_IONBF`（无缓冲模式）确保立即输出
- 配合 `fflush(stdout)` 强制刷新

### 4. Barrier 同步点

```cpp
MPI_Barrier(MPI_COMM_WORLD);  // 所有进程在此等待
```

**作用：**
- 确保所有进程到达同一执行点
- 用于阶段性同步（如输出前、输出后）
- 不会刷新标准输出缓冲区（需要手动 flush）

## 🎯 实际应用建议

### 场景 1：计算密集型任务

```cpp
if(rank == 0) {
    // 发送任务数据
    for(int i = 1; i < size; ++i) {
        MPI_Send(&task_data, size, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
} else {
    // 接收数据
    MPI_Recv(&task_data, size, MPI_INT, 0, 0, 
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    // ✅ 在这里完成计算！
    int result = compute(task_data);
    
    // 发送结果
    MPI_Send(&result, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
}
```

### 场景 2：写文件汇总

```cpp
// 方案 A：统一由 rank 0 写文件（推荐用于单个汇总文件）
if(rank == 0) {
    FILE* fp = fopen("results.txt", "w");
    for(int i = 1; i < size; ++i) {
        int result;
        MPI_Recv(&result, 1, MPI_INT, i, 0, 
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        fprintf(fp, "Rank %d: %d\n", i, result);
    }
    fclose(fp);
} else {
    MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}

// 方案 B：每个进程写自己的文件（推荐用于日志）
char filename[100];
sprintf(filename, "log_rank_%d.txt", rank);
FILE* fp = fopen(filename, "w");
fprintf(fp, "Rank %d result: %d\n", rank, value);
fclose(fp);
```

## 📚 相关概念

### MPI 通信模式

1. **点对点通信**（本项目）
   - `MPI_Send` / `MPI_Recv`
   - `MPI_Ssend` / `MPI_Recv`
   - `MPI_Isend` / `MPI_Irecv`（非阻塞）

2. **集合通信**
   - `MPI_Bcast`：广播
   - `MPI_Scatter`：分发
   - `MPI_Gather`：收集
   - `MPI_Reduce`：归约

3. **同步操作**
   - `MPI_Barrier`：栅栏同步

## ⚠️ 常见问题

### Q1: 输出顺序混乱？

**原因：** 多个进程同时写 stdout，操作系统缓冲导致。

**解决：**
1. 使用统一输出模式（rank 0 收集）
2. 设置无缓冲：`setvbuf(stdout, NULL, _IONBF, 0)`
3. 使用 `MPI_Barrier` 同步

### Q2: MPI_Init 调用失败？

**错误：** "MPI_Init() was called after MPI_FINALIZE"

**原因：** 在一个程序中多次调用 `MPI_Init/Finalize`

**解决：** 确保整个程序只有一对 `MPI_Init/Finalize`

### Q3: 死锁问题？

**场景：** 所有进程都在 `MPI_Recv` 等待

**原因：** 发送和接收不匹配

**解决：** 确保发送方和接收方配对正确

## 🔗 参考资源

- [MPI 官方标准](https://www.mpi-forum.org/)
- [Open MPI 文档](https://www.open-mpi.org/doc/)
- [Intel MPI 文档](https://www.intel.com/content/www/us/en/developer/tools/oneapi/mpi-library.html)

## 📝 许可证

本示例代码仅供学习和研究使用。

## 👤 作者

高性能计算 C++ 实践项目

