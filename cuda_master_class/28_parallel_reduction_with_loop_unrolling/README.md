# Loop Unrolling 并行归约

## 核心思想

**Loop Unrolling 的本质：减少 GPU Block 数量，让每个 Block 处理更多数据。**

## 原理说明

### 基本策略

以 **Unrolling 2** 为例：

1. **减少 Block 数量**
   - 原本：`grid = 数据总量 / blockDim.x`
   - 现在：`grid = 数据总量 / (blockDim.x × 2)`
   - 结果：Block 数量变成原来的 **1/2**

2. **每个 Block 处理更多数据**
   - 原本：每个 Block 处理 `blockDim.x` 个元素
   - 现在：每个 Block 处理 `blockDim.x × 2` 个元素
   - 关键计算：`BLOCK_OFFSET = blockIdx.x × blockDim.x × 2`

3. **两步归约**
   - **步骤1：预归约** - 每个线程把 2 个对应位置的数据相加，压缩成 1 个
   - **步骤2：Block内归约** - 复用上一节的算法，归约预归约后的结果

### 为什么要 `× 2`？

```
因为每个 Block 要处理 2 倍的数据，需要跳过前面 Block 负责的所有数据：

Block 0: BLOCK_OFFSET = 0 × 128 × 2 = 0    → 处理 input[0-255]
Block 1: BLOCK_OFFSET = 1 × 128 × 2 = 256  → 处理 input[256-511]
Block 2: BLOCK_OFFSET = 2 × 128 × 2 = 512  → 处理 input[512-767]
...
```

## 代码执行流程（以 Unrolling 4 为例）

### 数据：1024 个元素，blockDim.x = 128

```
不使用 unrolling:
  grid = 1024 / 128 = 8 个 Block
  每个 Block 处理 128 个元素

使用 unrolling 4:
  grid = 1024 / (128 × 4) = 2 个 Block  ← 只需要 2 个 Block！
  每个 Block 处理 512 个元素
```

### Block 0 的执行过程

```cuda
// Block 0 负责 input[0-511]（4 个数据段）
BLOCK_OFFSET = 0 × 128 × 4 = 0

// 步骤1：预归约（把 4 个数据段压缩成 1 个）
Thread 0:  input[0]   = input[0] + input[128] + input[256] + input[384]
Thread 1:  input[1]   = input[1] + input[129] + input[257] + input[385]
...
Thread 127: input[127] = input[127] + input[255] + input[383] + input[511]

// 现在 input[0-127] 包含了 4 个数据段的预归约结果

// 步骤2：Block内归约（复用上一节的算法）
// 归约 input[0-127] 这 128 个数 → 结果存到 input[0]
for(int offset = blockDim.x / 2; offset > 0; offset /= 2) {
    if (tid < offset) {
        i_data[tid] += i_data[tid + offset];
    }
    __syncthreads();
}

// 步骤3：保存结果
temp[0] = input[0]
```

## 关键代码

```cuda
__global__ void reduction_unrolling_blocks4(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    
    // 每个 Block 负责 4 × blockDim.x 个数据
    int BLOCK_OFFSET = blockIdx.x * blockDim.x * 4;
    int index = BLOCK_OFFSET + tid;
    int* i_data = input + BLOCK_OFFSET;
    
    // 步骤1：预归约 - 把 4 个数据段压缩成 1 个
    if ((index + 3 * blockDim.x) < size) {
        int a1 = input[index];
        int a2 = input[index + blockDim.x];
        int a3 = input[index + 2 * blockDim.x];
        int a4 = input[index + 3 * blockDim.x];
        input[index] = a1 + a2 + a3 + a4;
    }
    __syncthreads();
    
    // 步骤2：Block内归约（复用上一节代码）
    for(int offset = blockDim.x / 2; offset > 0; offset /= 2) {
        if (tid < offset) {
            i_data[tid] += i_data[tid + offset];
        }
        __syncthreads();
    }
    
    if (tid == 0) {
        temp[blockIdx.x] = i_data[0];
    }
}
```

## Main 函数调用

```cuda
int size = 1024;
int block_size = 128;
int unroll_factor = 4;  // 可以是 2, 4, 8...

// 关键：grid 要除以 unroll_factor
dim3 block(block_size);
dim3 grid((size / block_size) / unroll_factor);

int temp_size = grid.x;
int* d_input, *d_temp;
cudaMalloc(&d_input, size * sizeof(int));
cudaMalloc(&d_temp, temp_size * sizeof(int));

// 调用 kernel
reduction_unrolling_blocks4<<<grid, block>>>(d_input, d_temp, size);

// 复制中间结果
int* h_temp = (int*)malloc(temp_size * sizeof(int));
cudaMemcpy(h_temp, d_temp, temp_size * sizeof(int), cudaMemcpyDeviceToHost);

// CPU 继续累加
int result = 0;
for(int i = 0; i < temp_size; i++) {
    result += h_temp[i];
}
```

## 各方法对比

| 方法 | Grid Size | 每个Block处理 | 中间结果数 | 优点 |
|------|-----------|--------------|-----------|------|
| 不使用unrolling | 8 | 128个元素 | 8 | 简单 |
| Unrolling 2 | 4 | 256个元素 | 4 | Block数减半 |
| Unrolling 4 | 2 | 512个元素 | 2 | Block数减少75% |
| Unrolling 8 | 1 | 1024个元素 | 1 | 只需1个Block |

## 为什么这样做？

### 优点

1. **减少 Block 数量** → 降低 kernel 启动开销
2. **减少中间结果** → 降低 CPU 端累加工作
3. **提高 GPU 利用率** → 每个线程做更多工作

### 本质

```
原本：多个 Block 各自归约，CPU 再累加多个中间结果
现在：少数 Block 先预归约多个数据段，再做 Block 内归约

就像：
  原本 8 个人各算一道题，最后再把 8 个答案加起来
  现在 2 个人各算 4 道题的总和，最后只需加 2 个答案
```

## 编译运行

```bash
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Debug
./parallelReduction.exe
```

---

## 总结

**Loop Unrolling = 减少 Block 数 + 每个 Block 多干活 + 两步归约（预归约 + Block内归约）**

核心公式：
```
grid = 数据总量 / (blockDim.x × unroll_factor)
BLOCK_OFFSET = blockIdx.x × blockDim.x × unroll_factor
```

