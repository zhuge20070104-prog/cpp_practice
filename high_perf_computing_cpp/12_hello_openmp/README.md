# OpenMP 入门指南

## 🔍 OpenMP 是什么？

**OpenMP（Open Multi-Processing）** 是一个用于共享内存并行编程的API，支持C、C++和Fortran。

### ⚡ 核心特点

- **多线程模型**（不是多进程！）
- **共享内存架构**：所有线程共享同一进程的内存空间
- **编译器指令驱动**：使用 `#pragma` 指令控制并行化
- **跨平台支持**：在大多数架构和操作系统上都能工作

---

## 🧵 多线程 vs 多进程

### OpenMP 使用多线程

```
┌─────────────────────────────────────────┐
│         进程内存空间 (共享)              │
│  ┌──────┐  ┌──────┐  ┌──────┐          │
│  │线程1 │  │线程2 │  │线程3 │          │
│  └──────┘  └──────┘  └──────┘          │
│     ↓         ↓         ↓               │
│  共享全局变量、堆内存、代码段           │
└─────────────────────────────────────────┘
```

**优点**：
- ✅ 线程间通信快速（共享内存）
- ✅ 创建和销毁开销小
- ✅ 适合单机多核并行计算

### 多进程（如MPI）

```
┌──────────────┐  ┌──────────────┐  ┌──────────────┐
│   进程1      │  │   进程2      │  │   进程3      │
│   独立内存   │  │   独立内存   │  │   独立内存   │
└──────────────┘  └──────────────┘  └──────────────┘
       ↕                 ↕                 ↕
    需要进程间通信（IPC/网络）
```

**特点**：
- 内存隔离，需要显式通信
- 适合分布式系统和集群

---

## 🔧 OpenMP 工作原理

### Fork-Join 模型

```
主线程执行
    │
    ├─→ 遇到并行区域 (#pragma omp parallel)
    │
    ├─→ Fork：创建多个工作线程
    │        │
    │        ├── 线程1执行任务A
    │        ├── 线程2执行任务B
    │        └── 线程3执行任务C
    │        │
    ├─→ Join：所有线程同步，等待完成
    │
继续串行执行
```

### 执行流程示例

```cpp
#include <omp.h>
#include <iostream>

int main() {
    std::cout << "串行代码" << std::endl;
    
    // 并行区域开始 (Fork)
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        std::cout << "线程 " << tid << " 执行中" << std::endl;
    }
    // 并行区域结束 (Join)
    
    std::cout << "继续串行代码" << std::endl;
    return 0;
}
```

---

## 📦 WSL Ubuntu 环境安装验证

### 1️⃣ 检查 GCC 版本

```bash
gcc --version
```

**预期输出**：
```
gcc (Ubuntu 13.1.0-8ubuntu1~22.04) 13.1.0
```

> 💡 GCC 4.2+ 版本都内置支持 OpenMP

### 2️⃣ 验证 OpenMP 支持

```bash
echo '#include <omp.h>' | gcc -x c -fopenmp -E - > /dev/null 2>&1 && echo "✓ OpenMP已支持" || echo "✗ 需要安装"
```

**预期输出**：
```
✓ OpenMP已支持
```

### 3️⃣ 查看 OpenMP 版本

```bash
echo | gcc -fopenmp -dM -E - | grep -i openmp
```

**预期输出**：
```
#define _OPENMP 201511
```

> 版本号对照：
> - `200505` → OpenMP 2.5
> - `200805` → OpenMP 3.0
> - `201107` → OpenMP 3.1
> - `201307` → OpenMP 4.0
> - `201511` → OpenMP 4.5
> - `201811` → OpenMP 5.0

### 4️⃣ 如果未安装，执行以下命令

```bash
# 安装 OpenMP 开发库
sudo apt-get update
sudo apt-get install libomp-dev

# 或确保完整安装 GCC 工具链
sudo apt-get install build-essential
```

### 5️⃣ 测试编译

创建测试文件 `test_openmp.cpp`：

```cpp
#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        #pragma omp critical
        std::cout << "线程 " << tid << "/" << nthreads << std::endl;
    }
    return 0;
}
```

编译并运行：

```bash
g++ -fopenmp test_openmp.cpp -o test_openmp
./test_openmp
```

**预期输出**（线程数可能不同）：
```
线程 0/8
线程 1/8
线程 2/8
...
```

---

## 📝 CMake 配置

在 `CMakeLists.txt` 中添加 OpenMP 支持：

```cmake
cmake_minimum_required(VERSION 3.10)
project(hello_openmp LANGUAGES CXX)

# 查找 OpenMP
find_package(OpenMP REQUIRED)

# 创建可执行文件
add_executable(hello_openmp main.cpp)

# 链接 OpenMP 库
target_link_libraries(hello_openmp PRIVATE OpenMP::OpenMP_CXX)

# 或者手动添加编译标志
# target_compile_options(hello_openmp PRIVATE -fopenmp)
# target_link_options(hello_openmp PRIVATE -fopenmp)
```

---

## 🚀 常用编译选项

### GCC/Clang

```bash
# 基本编译
g++ -fopenmp program.cpp -o program

# 指定线程数（运行时）
export OMP_NUM_THREADS=4
./program

# 或在代码中设置
omp_set_num_threads(4);
```

### 优化选项

```bash
# 启用优化 + OpenMP
g++ -O3 -fopenmp -march=native program.cpp -o program
```

---

## 📚 OpenMP 基本语法

### 1. 并行区域

```cpp
#pragma omp parallel
{
    // 这段代码会被多个线程执行
}
```

### 2. 并行循环

```cpp
#pragma omp parallel for
for(int i = 0; i < N; i++) {
    // 循环迭代会自动分配给多个线程
}
```

### 3. 归约（Reduction）

```cpp
double sum = 0.0;
#pragma omp parallel for reduction(+:sum)
for(int i = 0; i < N; i++) {
    sum += array[i];
}
```

### 4. 数据共享子句

```cpp
int shared_var = 10;
int private_var;

#pragma omp parallel shared(shared_var) private(private_var)
{
    // shared_var: 所有线程共享
    // private_var: 每个线程有自己的副本
}
```

### 5. 临界区（Critical Section）

```cpp
#pragma omp parallel
{
    #pragma omp critical
    {
        // 同一时间只有一个线程能执行这段代码
        std::cout << "线程安全输出" << std::endl;
    }
}
```

---

## ⚠️ 常见陷阱

### 1. 竞争条件（Race Condition）

```cpp
// ❌ 错误：多个线程同时写入
int sum = 0;
#pragma omp parallel for
for(int i = 0; i < N; i++) {
    sum += array[i];  // 数据竞争！
}

// ✅ 正确：使用 reduction
int sum = 0;
#pragma omp parallel for reduction(+:sum)
for(int i = 0; i < N; i++) {
    sum += array[i];
}
```

### 2. False Sharing（伪共享）

```cpp
// ❌ 可能导致性能问题
double result[NUM_THREADS];
#pragma omp parallel
{
    int tid = omp_get_thread_num();
    result[tid] = compute();  // 数组元素可能在同一缓存行
}

// ✅ 改进：使用填充避免伪共享
struct alignas(64) PaddedResult {
    double value;
};
PaddedResult result[NUM_THREADS];
```

---

## 📊 性能提示

1. **合适的粒度**：并行任务不能太小，否则线程开销大于收益
2. **减少同步**：避免频繁使用 `critical`、`atomic`
3. **负载均衡**：使用 `schedule(dynamic)` 处理不均匀工作负载
4. **亲和性设置**：控制线程绑定到特定CPU核心

```bash
# 设置线程亲和性
export OMP_PROC_BIND=true
export OMP_PLACES=cores
```

---

## 🎓 总结

| 特性 | OpenMP | MPI |
|------|--------|-----|
| 并行模型 | 多线程 | 多进程 |
| 内存模型 | 共享内存 | 分布式内存 |
| 通信方式 | 直接访问共享变量 | 显式消息传递 |
| 适用场景 | 单机多核 | 集群/分布式 |
| 编程难度 | 相对简单 | 较复杂 |
| 安装要求 | GCC自带 | 需要安装MPI库 |

---

## 📖 参考资源

- [OpenMP 官方网站](https://www.openmp.org/)
- [OpenMP API 规范](https://www.openmp.org/specifications/)
- [GCC OpenMP 文档](https://gcc.gnu.org/onlinedocs/libgomp/)

---

**最后更新**: 2025-11-16

