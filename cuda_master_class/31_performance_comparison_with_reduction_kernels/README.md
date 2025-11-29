# 31. 并行 Reduction 性能比较

## 📝 项目概述

本项目实现了 8 种不同的 CUDA Reduction（归约）算法，并使用 Catch2 框架进行性能比较测试。

## 🎯 算法列表

1. **Warmup Kernel** - 预热 GPU
2. **Naive Neighbored Pairs** - 朴素相邻配对方法
3. **Improved Neighbored Pairs** - 改进的相邻配对方法
4. **Interleaved Pairs** - 交错配对方法
5. **2 Blocks Unrolling** - 2块数据展开
6. **8 Blocks Unrolling** - 8块数据展开
7. **Warp Unrolling + 8 Blocks** - Warp展开 + 8块数据展开
8. **Complete Unrolling** - 完全展开
9. **Complete Unrolling with Template** - 完全展开 + 模板函数

## 📊 性能优化技术

### 1. 朴素相邻配对（Naive Neighbored Pairs）
- 最基础的实现
- 存在严重的 warp divergence
- 性能较差，作为基准对比

### 2. 改进的相邻配对（Improved Neighbored Pairs）
- 减少了 warp divergence
- 使用块内局部指针优化内存访问

### 3. 交错配对（Interleaved Pairs）
- 进一步减少 warp divergence
- 更好的内存访问模式

### 4. 块展开（Block Unrolling）
- 减少循环迭代次数
- 每个线程块处理更多数据
- 提高并行度

### 5. Warp 展开（Warp Unrolling）
- 利用 warp 内线程的同步特性
- 最后 32 个线程不需要 `__syncthreads()`
- 使用 `volatile` 关键字避免编译器优化

### 6. 完全展开（Complete Unrolling）
- 完全消除循环
- 编译时确定所有迭代
- 最大化性能

### 7. 模板函数（Template Functions）
- 使用模板参数优化编译时展开
- 编译器可以更好地优化代码

## 🚀 构建和运行

### 前置要求
- CUDA Toolkit (12.0+)
- CMake (3.18+)
- Conan 1.x
- 支持 CUDA 的 NVIDIA GPU

### 构建步骤

```bash
cd 31_performance_comparison_with_reduction_kernels

# 如果 build 目录不存在，创建它
mkdir build
cd build

# 使用 Conan 安装依赖（Catch2）
conan install .. --build=missing

# 配置 CMake
cmake ..

# 编译
cmake --build . --config Release

# 运行测试
./parallelReduction       # Linux
.\Debug\parallelReduction.exe  # Windows Debug
.\Release\parallelReduction.exe  # Windows Release
```

### Windows 快速构建

```cmd
build.bat
cd build
.\Release\parallelReduction.exe
```

## 📈 测试数据

- **数据大小**: 128 MB (33,554,432 个整数)
- **Block Size**: 1024 threads
- **初始化方法**: INIT_ONE_TO_TEN (1-10 之间的随机数)

## 🔍 输出示例

```
=========================================================
Performance comparison of reduction for 128MB data array
=========================================================

CPU 执行时间: 0.045678 秒
CPU 结果: 184549376

预热 GPU...
预热完成

1. 朴素相邻配对方法 (Naive neighbored pairs)
Arrays are the same
GPU 执行时间（主机时钟）: 0.012345 秒

2. 改进的相邻配对方法 (Improved neighbored pairs)
Arrays are the same
GPU 执行时间（主机时钟）: 0.008765 秒

3. 交错配对方法 (Interleaved pairs)
Arrays are the same
GPU 执行时间（主机时钟）: 0.006543 秒

... （更多算法结果）

8. 完全展开 + 模板函数 (Complete unrolling with template)
Arrays are the same
GPU 执行时间（主机时钟）: 0.002134 秒

=========================================================
所有测试完成！
=========================================================
```

## 📚 关键概念

### Warp Divergence（Warp分歧）
- 同一个 warp 内的线程执行不同的指令路径
- 导致串行执行，降低性能
- 通过改进算法可以减少

### Shared Memory（共享内存）
- 块内线程共享的高速缓存
- 比全局内存快得多
- 需要 `__syncthreads()` 同步

### Loop Unrolling（循环展开）
- 减少循环控制开销
- 增加指令级并行性
- 编译器可以更好地优化

### Template Metaprogramming（模板元编程）
- 编译时计算
- 根据参数生成特化代码
- 零运行时开销

## 🔧 性能分析工具

可以使用 NVIDIA Nsight Compute 进行详细分析：

```bash
# 分析特定测试用例
ncu --set full -o profile_result ./parallelReduction

# 查看 warp 执行效率
ncu --metrics smsp__sass_thread_inst_executed_op_*_pred_on.sum ./parallelReduction
```

## 📖 参考资料

- NVIDIA CUDA C Programming Guide
- Optimizing Parallel Reduction in CUDA (Mark Harris)
- CUDA Best Practices Guide

## 🤝 贡献

欢迎提交问题和改进建议！

## 📄 许可证

本项目仅用于学习和研究目的。

