## 32. CUDA Dynamic Parallelism（动态并行）

这个小例子对应你截图里老师讲的那段代码，用来**演示 CUDA 动态并行的概念**，而不是做性能优化。

### 1. 程序功能概览

- Host 端启动一个 **parent kernel**：
  - 配置：`<<<1, 16>>>`，也就是 **1 个 block，16 个线程**。
- 在 parent kernel 里：
  - 每个线程都会 `printf("Depth: d - tid: x")` 打印自己所在的深度和值。
  - 只让 `threadIdx.x == 0` 的线程负责再启动一个 **child kernel**：
    - child 的线程数是上一层的一半：`size / 2`。
    - 传入的 `depth` 参数加 1。
- 如此递归下去，线程数序列就是：
  - 第 0 层：16 个 thread
  - 第 1 层：8 个 thread
  - 第 2 层：4 个 thread
  - 第 3 层：2 个 thread
  - 第 4 层：1 个 thread（`size == 1`，递归结束）

### 2. 关键 kernel 代码

你可以对照着自己手敲一遍：

```cpp
__global__ void dynamic_parallelism_check(int size, int depth) {
    printf("Depth: %d - tid: %d\n", depth, threadIdx.x);

    // 递归结束条件：只剩 1 个线程
    if (size == 1) {
        return;
    }

    // 只让 tid==0 的线程负责 launch 下一层 child grid
    if (threadIdx.x == 0) {
        int child_size = size / 2;
        dynamic_parallelism_check<<<1, child_size>>>(child_size, depth + 1);
    }
}
```

Host 端 `main` 很简单：

```cpp
int main(int argc, char** argv) {
    int size = 16;   // 第一层 16 个线程
    int depth = 0;   // 从 0 层开始

    printf("CUDA Dynamic Parallelism - Simple Demo\n");
    printf("Parent grid: 1 block, %d threads\n\n", size);

    dynamic_parallelism_check<<<1, size>>>(size, depth);

    cudaDeviceSynchronize();
    cudaDeviceReset();
    return 0;
}
```

### 3. 两个参数 `size` 和 `depth` 的含义

- **`size`**：当前这一层 child grid 的线程数（也是 `<<<1, size>>>` 里的第二个参数）。
  - 用来控制「当前层有多少线程」以及「下一层要不要继续递归」。
  - 当 `size == 1` 时，不再 launch 子 kernel，递归结束。
- **`depth`**：当前递归的深度，只用来辅助打印，方便你在输出中看到：
  - `Depth: 0 - tid: 0..15`
  - `Depth: 1 - tid: 0..7`
  - 一直到 `Depth: 4 - tid: 0`。

### 4. 为什么只让 `threadIdx.x == 0` 去 launch child？

如果所有线程都写：

```cpp
dynamic_parallelism_check<<<1, size / 2>>>(size / 2, depth + 1);
```

那一层有多少个线程，就会 launch 多少次 child grid：

- depth 0 有 16 个线程 → 16 个 child grid；
- depth 1 每个 child 又各自 launch 8 线程的 grid，结构会变得很乱。

为了得到一棵**非常干净的“每层只有一个 child grid”的递归树**，例子里只选了一个代表线程（`tid == 0`）去 launch 下一层。

### 5. 动态并行编译要点（本仓库 CMake 已经帮你配好）

CUDA 动态并行有两个重要前提：

1. **计算能力要足够高**：本项目中已经设置为 Ada 架构 `89`，完全没问题。
2. **编译时要打开可重定位设备代码 `-rdc=true` 并启用可分离编译**。

在 `CMakeLists.txt` 里已经配置好了：

- `set_target_properties(parallelReduction PROPERTIES CUDA_SEPARABLE_COMPILATION ON)`
- `target_compile_options(... -rdc=true ...)`

你只需要像其他章节一样：

```bash
cd 32_cuda_dynamic_parallism
mkdir build
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Release
```

然后运行：

```bash
./parallelReduction        # Linux
.\Release\parallelReduction.exe   # Windows
```

### 6. 这个例子想展示什么？

1. **语法层面**：在 `__global__` 函数内部再次使用 `<<< >>>` 启动 kernel。
2. **结构层面**：通过 `size` / `depth` 打印出一棵很清晰的递归调用树。
3. **执行时序层面**：
   - parent grid 会在 child grid 完成前挂起等待；
   - 在 profiler 里能看到嵌套的 kernel 时间线。

它比前面那些 reduction 优化要“纯概念”得多，非常适合拿来练习 CUDA 动态并行的基本思路。


