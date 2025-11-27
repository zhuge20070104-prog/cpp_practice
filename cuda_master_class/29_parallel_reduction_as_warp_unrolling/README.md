# CUDA 并行归约 - Warp Unrolling 优化

## 📚 核心问题

在使用 **interleaved pair** 归约时，最后几轮迭代存在严重的 **Warp Divergence** 问题。

### 问题分析

```cuda
for(int offset = blockDim.x/2; offset > 0; offset /= 2) {
    if (tid < offset) {  // ← 问题在这里！
        i_data[tid] += i_data[tid + offset];
    }
    __syncthreads();
}
```

**当 offset < 32 时，只有第一个 Warp 工作，且有 Warp Divergence！**

---

## 🔍 详细迭代过程分析

### 场景：128个数据，blockDim.x = 128

#### 迭代1：offset = 64 ✓

```
活跃线程: Thread 0-63（前2个Warp）

Warp 0 (Thread 0-31):  全部工作 ✓
Warp 1 (Thread 32-63): 全部工作 ✓
Warp 2 (Thread 64-95): 全部不工作
Warp 3 (Thread 96-127): 全部不工作

Warp Divergence: 无 ✓
```

#### 迭代2：offset = 32 ✓

```
活跃线程: Thread 0-31（第1个Warp）

Warp 0 (Thread 0-31):  全部工作 ✓
Warp 1-3: 全部不工作

Warp Divergence: 无 ✓
```

#### 迭代3：offset = 16 ⚠️ 问题开始！

```
活跃线程: Thread 0-15

Warp 0 (Thread 0-31):
  - Thread 0-15:  工作 ✓
  - Thread 16-31: 不工作 ✗
  
Warp Divergence: 有！⚠️
(同一个Warp内部分线程工作，部分不工作)

图示:
┌───────────┬───────────┐
│ Thread    │ Thread    │  ← 第1个Warp
│ 0-15      │ 16-31     │
│ 工作 ✓    │ 不工作 ✗  │
└───────────┴───────────┘
     ⚠️ Warp Divergence！
```

#### 迭代4-7：offset = 8, 4, 2, 1

```
全部都有 Warp Divergence！⚠️

迭代4 (offset=8):  Thread 0-7  工作，Thread 8-31  不工作
迭代5 (offset=4):  Thread 0-3  工作，Thread 4-31  不工作
迭代6 (offset=2):  Thread 0-1  工作，Thread 2-31  不工作
迭代7 (offset=1):  Thread 0    工作，Thread 1-31  不工作
```

### 问题总结

```
迭代轮次    offset    Warp Divergence
────────────────────────────────────
第1轮       64        无 ✓
第2轮       32        无 ✓
第3轮       16        有 ⚠️  ← 从这里开始！
第4轮       8         有 ⚠️
第5轮       4         有 ⚠️
第6轮       2         有 ⚠️
第7轮       1         有 ⚠️
```

---

## 💡 Warp Unrolling 解决方案

### 核心思想

**当只剩1个Warp（32个线程）时，手动展开循环，消除 if 分支！**

### 代码实现

```cuda
__global__ void reduction_warp_unrolling(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    int* i_data = input + blockDim.x * blockIdx.x;

    // 步骤1：正常循环，直到只剩1个Warp
    for(int offset = blockDim.x / 2; offset > 32; offset /= 2) {
        if (tid < offset) {
            i_data[tid] += i_data[tid + offset];
        }
        __syncthreads();
    }

    // 步骤2：手动展开最后1个Warp（消除Warp Divergence）
    if (tid < 32) {
        // volatile: 防止编译器优化，强制立即写入内存
        volatile int* vsmem = i_data;
        
        // 手动展开，没有 if 分支！
        vsmem[tid] += vsmem[tid + 32];  // offset = 32
        vsmem[tid] += vsmem[tid + 16];  // offset = 16
        vsmem[tid] += vsmem[tid + 8];   // offset = 8
        vsmem[tid] += vsmem[tid + 4];   // offset = 4
        vsmem[tid] += vsmem[tid + 2];   // offset = 2
        vsmem[tid] += vsmem[tid + 1];   // offset = 1
        
        // 不需要 __syncthreads()！
        // Warp内的32个线程是硬件同步的
    }

    if (tid == 0) {
        temp[blockIdx.x] = i_data[0];
    }
}
```

---

## 🎯 为什么这样有效？

### 1. 消除 if 分支

```
原来（有Warp Divergence）:
  if (tid < 16) {  ← 有分支判断
      i_data[tid] += i_data[tid + 16];
  }
  // Warp内部分线程工作，部分不工作 ⚠️

现在（无Warp Divergence）:
  if (tid < 32) {  ← 整个Warp要么全进入，要么全不进入
      volatile int* vsmem = i_data;
      vsmem[tid] += vsmem[tid + 16];  ← 没有if分支！
      vsmem[tid] += vsmem[tid + 8];
      // 所有32个线程都执行相同指令 ✓
  }
```

### 2. Warp 内天然同步

**Warp = GPU硬件调度的最小单元 = 32个线程**

特点：
- 同时执行同一条指令（SIMT）
- 天然同步，不需要 `__syncthreads()`
- 访问速度快

```
同一个Warp的32个线程：
  Thread 0: vsmem[0] += vsmem[16];  ┐
  Thread 1: vsmem[1] += vsmem[17];  │
  ...                               ├─ 同时执行
  Thread 31: vsmem[31] += vsmem[47];┘
  
  执行完毕后，所有线程自动同步 ✓
```

### 3. volatile 关键字的作用

```cuda
volatile int* vsmem = i_data;
```

**作用：防止编译器过度优化，确保每次都从内存读写！**

```
没有 volatile:
  编译器可能优化成:
    temp = vsmem[tid];
    temp += vsmem[tid + 16];
    temp += vsmem[tid + 8];
    vsmem[tid] = temp;
  
  问题：中间结果没有写回内存，其他线程看不到！

有 volatile:
  每次累加都立即写回内存:
    vsmem[tid] += vsmem[tid + 16];  // 立即写回
    vsmem[tid] += vsmem[tid + 8];   // 读取更新后的值
    
  保证：其他线程能立即看到最新值 ✓
```

---

## 📊 完整执行示例

### 32个数据的Warp Unrolling过程

```
初始数据: [d0, d1, d2, ..., d31]
32个线程: Thread 0-31

执行: vsmem[tid] += vsmem[tid + 16];
┌────────────────┬────────────────┐
│ Thread 0-15    │ Thread 16-31   │
│ 把 [0-15] 和   │ 也执行，但结果  │
│    [16-31] 相加 │ 不重要         │
└────────────────┴────────────────┘

结果: [d0', d1', ..., d15', 旧数据, ...]
     └─ 包含了两个数的和


执行: vsmem[tid] += vsmem[tid + 8];
┌────────┬────────┬────────────────┐
│ T 0-7  │ T 8-15 │ T 16-31        │
│ 有效   │ 也执行  │ 也执行         │
└────────┴────────┴────────────────┘

结果: [d0'', d1'', ..., d7'', 旧数据, ...]


执行: vsmem[tid] += vsmem[tid + 4];
结果: [d0''', d1''', d2''', d3''', 旧数据, ...]


执行: vsmem[tid] += vsmem[tid + 2];
结果: [d0'''', d1'''', 旧数据, ...]


执行: vsmem[tid] += vsmem[tid + 1];
结果: [最终和, 旧数据, ...]
      ↑
    vsmem[0] 包含所有数据的和！
```

---

## 🚀 完整优化：Loop Unrolling + Warp Unrolling

### 代码

```cuda
__global__ void reduction_complete_unrolling4(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    
    // 步骤1：Loop Unrolling（每个block处理4倍数据）
    int BLOCK_OFFSET = blockIdx.x * blockDim.x * 4;
    int index = BLOCK_OFFSET + tid;
    int* i_data = input + BLOCK_OFFSET;
    
    if ((index + 3 * blockDim.x) < size) {
        int a1 = input[index];
        int a2 = input[index + blockDim.x];
        int a3 = input[index + 2 * blockDim.x];
        int a4 = input[index + 3 * blockDim.x];
        input[index] = a1 + a2 + a3 + a4;
    }
    __syncthreads();
    
    // 步骤2：Block内归约（到只剩1个Warp）
    for(int offset = blockDim.x / 2; offset > 32; offset /= 2) {
        if (tid < offset) {
            i_data[tid] += i_data[tid + offset];
        }
        __syncthreads();
    }
    
    // 步骤3：Warp Unrolling（最后1个Warp）
    if (tid < 32) {
        volatile int* vsmem = i_data;
        vsmem[tid] += vsmem[tid + 32];
        vsmem[tid] += vsmem[tid + 16];
        vsmem[tid] += vsmem[tid + 8];
        vsmem[tid] += vsmem[tid + 4];
        vsmem[tid] += vsmem[tid + 2];
        vsmem[tid] += vsmem[tid + 1];
    }
    
    if (tid == 0) {
        temp[blockIdx.x] = i_data[0];
    }
}
```

### Main 函数调用

```cuda
int size = 1024;
int block_size = 128;
int unroll_factor = 4;

// Grid size要除以unroll_factor
dim3 block(block_size);
dim3 grid((size / block_size) / unroll_factor);  // = 2

int temp_size = grid.x;
int* d_input, *d_temp;
cudaMalloc(&d_input, size * sizeof(int));
cudaMalloc(&d_temp, temp_size * sizeof(int));

// 调用kernel
reduction_complete_unrolling4<<<grid, block>>>(d_input, d_temp, size);

// 复制结果
int* h_temp = (int*)malloc(temp_size * sizeof(int));
cudaMemcpy(h_temp, d_temp, temp_size * sizeof(int), cudaMemcpyDeviceToHost);

// CPU继续累加（只需加2个数！）
int result = h_temp[0] + h_temp[1];
```

---

## 📈 性能对比

### 各方法对比（1024个数据，block_size=128）

| 方法 | Grid Size | Warp Divergence | __syncthreads()次数 | 性能 |
|------|-----------|-----------------|-------------------|------|
| 基础 interleave | 8 | 最后5轮有 ⚠️ | 7次 | 慢 |
| Warp Unrolling only | 8 | 无 ✓ | 2次 | 较快 |
| Loop Unrolling 4 | 2 | 最后5轮有 ⚠️ | 7次 | 较快 |
| **完整优化 (4)** | **2** | **无 ✓** | **2次** | **最快 🚀** |
| **完整优化 (8)** | **1** | **无 ✓** | **2次** | **最快 🚀** |

### 优化收益

1. **消除 Warp Divergence**
   - 最后5轮迭代：从有分支 → 无分支
   - 提高 Warp 执行效率

2. **减少同步开销**
   - __syncthreads()：从7次 → 2次
   - Warp内不需要同步

3. **减少 Block 数量**
   - Loop Unrolling 8: 从8个Block → 1个Block
   - 降低 kernel 启动开销

---

## 🔑 关键概念总结

### Warp 的特性

```
Warp = 32个线程
  - GPU硬件调度的最小单元
  - 同时执行同一条指令（SIMT）
  - 天然同步，不需要 __syncthreads()
  - 分支判断会导致 Warp Divergence
```

### Warp Divergence

```
定义: 同一个Warp内的线程执行不同的分支

发生情况:
  if (tid < 16) {  ← 在Warp内部分线程满足，部分不满足
      ...
  }

后果:
  - 硬件必须串行执行两个分支
  - 降低并行度
  - 影响性能
```

### Warp Unrolling

```
方法: 手动展开循环，消除 if 分支

适用场景:
  - 只有1个Warp工作时（线程数 ≤ 32）
  - 迭代次数固定

好处:
  - 无 Warp Divergence
  - 不需要 __syncthreads()
  - 执行效率高
```

---

## 📝 编译运行

```bash
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Debug
./parallelReduction.exe
```

---

## 🎯 总结

### 核心要点

1. **Warp = 32个线程，是GPU硬件调度单位**

2. **当 offset < 32 时，原算法有 Warp Divergence**

3. **Warp Unrolling = 手动展开最后几轮循环**

4. **Warp内线程天然同步，不需要 `__syncthreads()`**

5. **`volatile` 防止编译器优化，保证内存可见性**

### 优化组合

```
最佳实践 = Loop Unrolling + Warp Unrolling

效果:
  ✓ 减少 Block 数量（Loop Unrolling）
  ✓ 消除 Warp Divergence（Warp Unrolling）
  ✓ 减少同步开销
  ✓ 提高整体性能 🚀
```

### 记忆口诀

```
Loop Unrolling: 让每个Block多干活，减少Block数
Warp Unrolling: 手动展开最后32个线程，消除分支
两者结合: 性能最优！
```

