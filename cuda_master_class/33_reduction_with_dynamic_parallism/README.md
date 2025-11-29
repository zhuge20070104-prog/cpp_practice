## 33. Reduction with Dynamic Parallelism（动态并行归约）

本章节对应你截图里的 **“递归 + 动态并行的 reduction kernel”**。  
核心思想是：**用递归的子 kernel 替代传统 `for + __syncthreads()` 的多轮归约循环**。

---

### 1. 基本思路回顾

- **传统 block 内归约（interleaved pairs）** 的写法大致是：
  - 设 `isize = blockDim.x`，每一轮 `istride = isize >> 1`；
  - 每一轮中，让 `tid < istride` 的线程做：
    - \( i\_data[tid] += i\_data[tid + istride] \)
  - 然后 `__syncthreads()`，再把 `istride` 减半，继续下一轮；
  - 最后 `i_data[0]` 就是这个 block 的部分和。

在课程中的 **动态并行版本** 里，老师把「多轮循环」换成了「多层递归 kernel」：

- **参数含义**
  - `isize`：当前这一层参与归约的有效元素个数（例如一开始是 64）。
  - `istride = isize >> 1`：当前这一层的 offset。
- **每一层做的事情**
  - 有效线程：`tid < istride`；
  - 计算：`g_idata[tid] += g_idata[tid + istride];`
  - 然后只让 `tid == 0` 再 `launch` 下一层 child kernel：
    - 线程数变成上一层的一半：`<<<1, istride>>>`
    - 有效元素个数也变成 `istride`
- **递归结束条件**
  - 当 `isize == 1` 时，不再 launch 子 kernel，`g_idata[0]` 就是整个数组的和。

这样就形成了一棵非常清晰的递归调用树：

- 层 0：`<<<1, 64>>>`，处理 64 个元素  
- 层 1：`<<<1, 32>>>`，处理 32 个元素  
- 层 2：`<<<1, 16>>>`  
- … 一直到  
- 最后一层：`<<<1, 1>>>`，只剩一个线程，写回结果。

---

### 2. 关键 kernel 代码结构

本目录中的 `parallelReduction.cu` 实现如下逻辑（只保留核心结构，便于对照视频）：

```cpp
__global__ void gpuRecursiveReduce(int* g_idata, int* g_odata, unsigned int isize) {
    unsigned int tid = threadIdx.x;

    // 1) 递归结束条件：只剩 1 个有效元素
    if (isize == 1) {
        if (tid == 0) {
            g_odata[0] = g_idata[0];
        }
        return;
    }

    // 2) 本层的 offset / istride
    unsigned int istride = isize >> 1;

    // 3) 本层做一次 interleaved-pairs 相加
    if (tid < istride) {
        g_idata[tid] += g_idata[tid + istride];
    }

    // 4) 只让 tid==0 发射下一层 child grid
    if (tid == 0) {
        gpuRecursiveReduce<<<1, istride>>>(g_idata, g_odata, istride);
    }
}
```

Host 端只需要 launch **第一层**：

```cpp
const int isize = 64;          // 方便对应 PPT 中 “isize = 64”
gpuRecursiveReduce<<<1, isize>>>(d_idata, d_odata, isize);
cudaDeviceSynchronize();
```

所有后续的 kernel 都是在 device 端递归产生的。

---

### 3. 为什么这些 `__syncthreads()` / `cudaDeviceSynchronize()` 可以省掉？

你在截图里能看到老师一开始写了不少同步：

- 每一层归约之后的 `__syncthreads();`
- device 端的 `cudaDeviceSynchronize();`

最后都被注释掉了，并且写着「这些 sync 都是不需要的」。

背后的原因（在这个 demo 里）可以简化理解为：

- **kernel 之间天然是“全局同步”的**：
  - 当前层的 kernel 完全结束以后，下一层的 kernel 才会真正开始执行；
  - 也就是说，child kernel 看到的全局内存，一定是「前一层所有线程都写完之后」的状态；
  - 所以不需要再在 block 内加一次 `__syncthreads()`。
- **dynamic parallelism 下的父子 kernel 关系**：
  - parent kernel 在 “逻辑上” 要等所有 child kernel 都结束，它自己才算结束；
  - 因此在 host 端最后只需要一次 `cudaDeviceSynchronize()`，就能保证所有递归层级都执行完。

注意：这只是在本例这种 **简单单 block + 纯全局内存归约** 的场景里可以安全省略。  
在更复杂的场景中，是否可以去掉同步，还是要结合 **并发结构 / 共享内存使用方式 / 多 block 交互** 具体分析。

---

### 4. main 函数做了什么？

`parallelReduction.cu` 的 `main` 做了几件简单的事：

- **准备输入**
  - 数组长度：`isize = 64`；
  - 使用 `initialize(..., INIT_ONE)` 把所有元素初始化为 1；
  - 用 `reduction_cpu` 在 CPU 上做一次求和，得到对比基准。
- **拷贝到 GPU 并 launch kernel**
  - `cudaMalloc` 分配 `d_idata` / `d_odata`；
  - `cudaMemcpy` 把 host 数据拷到 `d_idata`；
  - 启动 `gpuRecursiveReduce<<<1, 64>>>`。
- **取回结果并比较**
  - 把 `d_odata[0]` 拷回 host；
  - 使用 `compare_results(gpu_result, cpu_result)` 打印 GPU / CPU 的结果是否一致。

这样你可以非常直观地看到：**递归动态并行版本和普通 CPU 归约给出的结果是一致的**。

---

### 5. 编译与运行（CMake + Conan）

本章节的 `CMakeLists.txt` 已经帮你配置好了：

- 开启了 **可分离编译**：`CUDA_SEPARABLE_COMPILATION ON`
- 为 CUDA 编译器加上了 **`-rdc=true`** 选项（动态并行必须）
- 链接了上层 `common` 目录下的工具函数

#### 5.1 使用 CMake（推荐）

在 Windows 上（PowerShell 或 CMD）：

```bash
cd 33_reduction_with_dynamic_parallism
mkdir build
cd build

conan install .. --build=missing
cmake ..
cmake --build . --config Debug   # 或 Release
```

生成的可执行文件大致在：

- `.\bin\parallelReduction.exe` 或
- `.\Debug\parallelReduction.exe`（视你的 CMake 生成器而定）

运行：

```bash
.\bin\parallelReduction.exe
```

你会看到类似输出：

- 程序标题（33. Reduction with Dynamic Parallelism）
- 数组大小、launch 配置
- GPU / CPU 结果对比是否一致

#### 5.2 使用本目录自带的 `build.bat`

你也可以直接在 `build` 目录（或空目录）里运行：

```bash
cd 33_reduction_with_dynamic_parallism
mkdir build
cd build

..\build.bat
```

`build.bat` 会：

- 调用 Conan + CMake 完成编译；
- 然后用 Nsight Systems (`nsys`) 对生成的 `parallelReduction.exe` 做一次简单的性能/时间线采样。

---

### 6. 和第 31 章、32 章的关系

- **第 31 章**：集中讲各种 **block 内归约优化**（neighbored pairs、interleaved、unrolling、warp unrolling 等）。
- **第 32 章**：用一个非常简单的 demo 介绍 **CUDA 动态并行的语法和执行流程**。
- **本第 33 章**：把这两块内容组合在一起，做一个 **“使用动态并行完成归约”的练习**：
  - 算法还是第 31 章里那种“每一层线程数减半”的 pair-wise reduction；
  - 但“多轮循环 + `__syncthreads()`”被换成了“多层递归 kernel 调用”，更直观地演示了 dynamic parallelism 的威力和开销。

你可以在掌握这一章之后，继续思考：

- 如果把多个 block 的部分和也用动态并行再做一层递归，会不会更快？  
  提示：**未必**，因为 launch kernel 本身也有不小的开销，这也是老师在 ppt 中提到的“launch 几个 kernel 太多会抵消并行带来的好处”。


