# CUDA Warp 详解

## 什么是 Warp？

**Warp** 是 CUDA 中线程调度和执行的基本单位。一个 warp 包含 **32 个连续的线程**，这些线程以 SIMT (Single Instruction, Multiple Thread) 方式同步执行。

### 关键特性
- 每个 warp 固定包含 **32 个线程**
- 同一个 warp 内的线程执行相同的指令（但数据可能不同）
- 线程块（block）会被分成多个 warp
- 如果线程数不是 32 的倍数，最后一个 warp 会有部分线程不活跃

## Warp ID 的计算

### 块内 Warp ID (Local Warp ID)

对于 **1D 线程块**，块内 warp ID 的计算非常简单：

```cuda
int warp_id = threadIdx.x / 32;
```

**原理：**
- threadIdx.x = 0-31  → warp_id = 0 (第一个 warp)
- threadIdx.x = 32-63 → warp_id = 1 (第二个 warp)
- threadIdx.x = 64-95 → warp_id = 2 (第三个 warp)
- 以此类推...

### 多维线程块的 Warp ID

对于 **2D 或 3D 线程块**，需要先计算线程在块内的线性索引：

```cuda
// 2D 线程块
int local_tid = threadIdx.y * blockDim.x + threadIdx.x;
int warp_id = local_tid / 32;

// 3D 线程块
int local_tid = threadIdx.z * blockDim.x * blockDim.y 
              + threadIdx.y * blockDim.x 
              + threadIdx.x;
int warp_id = local_tid / 32;
```

### 全局 Warp ID (Global Warp ID)

如果需要跨多个 block 计算全局唯一的 warp ID：

```cuda
// 计算每个 block 有多少个 warp（向上取整）
int warps_per_block = (blockDim.x + 31) / 32;

// 计算全局 block ID
int gbid = gridDim.x * blockIdx.y + blockIdx.x;

// 计算全局 warp ID
int global_warp_id = gbid * warps_per_block + warp_id;
```

## 代码示例分析

### 配置
```cuda
dim3 block_size(42);   // 每个 block 有 42 个线程
dim3 grid_size(2, 2);  // 2x2 的 grid，共 4 个 blocks
```

### Warp 分布
- **每个 block**：42 个线程 ÷ 32 = 1 余 10
  - warp 0: 线程 0-31 (完整，32 个线程)
  - warp 1: 线程 32-41 (不完整，10 个线程)
  
- **总共**：4 blocks × 2 warps = **8 个 warp**

### 输出示例

```
Block (0,0), gbid=0:
  tid: 0-31  → warp_id = 0
  tid: 32-41 → warp_id = 1

Block (1,0), gbid=1:
  tid: 0-31  → warp_id = 0
  tid: 32-41 → warp_id = 1

Block (0,1), gbid=2:
  tid: 0-31  → warp_id = 0
  tid: 32-41 → warp_id = 1

Block (1,1), gbid=3:
  tid: 0-31  → warp_id = 0
  tid: 32-41 → warp_id = 1
```

**重要观察：**
- 每个 block 内的 warp_id 都是从 0 开始
- warp_id 是块内相对编号，不是全局唯一的
- 不同 block 中相同的 warp_id 代表不同的物理 warp

## 为什么理解 Warp 很重要？

### 1. 性能优化
- **Warp divergence（分支分歧）**：同一 warp 内的线程如果执行不同的分支，会串行执行，降低性能
- **内存合并（Memory Coalescing）**：同一 warp 内的线程访问连续内存可以合并成一次访问

### 2. 共享内存访问
- Bank conflict 的分析和优化需要理解 warp 的行为

### 3. 原子操作
- 同一 warp 内的原子操作可能有特殊的优化

## 最佳实践

### ✅ 好的做法
1. **线程块大小是 32 的倍数**：避免 warp 中有不活跃的线程浪费资源
   ```cuda
   dim3 block_size(64);   // ✓ 2 个完整的 warp
   dim3 block_size(128);  // ✓ 4 个完整的 warp
   dim3 block_size(256);  // ✓ 8 个完整的 warp
   ```

2. **避免 warp divergence**：
   ```cuda
   // ✗ 不好：warp 内有不同分支
   if (threadIdx.x % 2 == 0) {
       // 一半线程执行这里
   } else {
       // 另一半线程执行这里
   }
   
   // ✓ 好：按 warp 边界划分
   if (threadIdx.x < 32) {
       // warp 0 执行
   } else {
       // warp 1 执行
   }
   ```

3. **内存访问对齐**：确保同一 warp 的线程访问连续内存地址

### ❌ 避免的做法
```cuda
dim3 block_size(42);   // ✗ 不是 32 的倍数，最后 10 个线程浪费一个 warp
dim3 block_size(100);  // ✗ 不是 32 的倍数，最后 4 个线程浪费一个 warp
```

## 扩展阅读

- NVIDIA CUDA Programming Guide: Warp Scheduling
- 理解 SIMT 架构
- Warp-level primitives (从 CUDA 9.0 开始)

## 相关概念

- **SM (Streaming Multiprocessor)**：物理执行单元，可以同时执行多个 warp
- **Block**：线程组织的逻辑单位，由多个 warp 组成
- **Grid**：多个 block 的集合
- **Thread**：最小的执行单位，32 个线程组成一个 warp

