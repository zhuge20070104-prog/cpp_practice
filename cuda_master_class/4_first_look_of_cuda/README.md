# CUDA 向量加法示例

## 程序说明

这是一个简单的 CUDA 程序，演示如何使用 GPU 并行计算两个向量的加法。

### 关键部分解释

#### 1. Kernel 启动配置（你提到的关键问题）

```cuda
addKernel<<<1, size>>>(dev_c, dev_a, dev_b);
```

**语法：** `kernelFunction<<<gridSize, blockSize>>>(参数)`

- **第一个参数（1）**：网格大小（Grid Size）- 表示有多少个线程块
- **第二个参数（size）**：线程块大小（Block Size）- 表示每个线程块有多少个线程

在这个例子中：
- 使用 1 个线程块
- 每个线程块有 5 个线程（对应数组大小）

#### 2. 线程索引

```cuda
int i = threadIdx.x;
```

- `threadIdx.x` 获取当前线程在线程块中的索引（0-4）
- 每个线程处理数组中的一个元素

#### 3. 程序流程

1. **分配 GPU 内存**：使用 `cudaMalloc`
2. **数据传输到 GPU**：使用 `cudaMemcpy` (Host → Device)
3. **启动 Kernel**：在 GPU 上并行执行
4. **同步等待**：使用 `cudaDeviceSynchronize`
5. **结果传回 CPU**：使用 `cudaMemcpy` (Device → Host)
6. **释放 GPU 内存**：使用 `cudaFree`

## 编译和运行

### 使用 CMake 编译

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目
cmake ..

# 编译
cmake --build .

# 运行
./vectorAdd
```

### 清理

```bash
# 删除 build 目录
rm -rf build
```

## 预期输出

```
{ 1, 2, 3, 4, 5 } + { 10, 20, 30, 40, 50 } = { 11, 22, 33, 44, 55 }
```

## 注意事项

- 需要安装 NVIDIA CUDA Toolkit
- 需要支持 CUDA 的 GPU
- 线程块大小有限制（通常最大 1024 个线程）
- 对于更大的数组，需要使用多个线程块

## 故障排查

### 问题：CUDA 和 GCC 版本不兼容

**错误信息：** `error: invalid combination of type specifiers` 或 `_Float128` 相关错误

**原因：** CUDA 12.4 不完全支持 GCC 13.x

**解决方案 1（推荐）：** 安装兼容的 GCC 版本

```bash
# 安装 GCC-12（CUDA 12.x 完全支持）
sudo apt update
sudo apt install gcc-12 g++-12

# 清理旧的构建文件
cd build
rm -rf *

# 重新配置（CMakeLists.txt 会自动使用 gcc-12）
cmake ..
cmake --build .
```

**解决方案 2：** 手动指定 CUDA 主机编译器

```bash
cd build
rm -rf *
cmake -DCMAKE_CUDA_HOST_COMPILER=/usr/bin/gcc-12 ..
cmake --build .
```

**CUDA 和 GCC 兼容性表：**
- CUDA 12.x: 推荐 GCC 11 或 12
- CUDA 11.x: 推荐 GCC 9, 10 或 11
- CUDA 10.x: 推荐 GCC 7 或 8

### 问题：CMake 找不到 CUDA 编译器

如果遇到 "CUDA compiler identification is unknown" 错误：

1. **检查 CUDA 是否安装**
```bash
nvcc --version
```

2. **如果未安装 CUDA，需要先安装 NVIDIA CUDA Toolkit**
```bash
# Ubuntu/Debian
# 访问 https://developer.nvidia.com/cuda-downloads 下载安装
```

3. **设置环境变量**（添加到 `~/.bashrc` 或 `~/.zshrc`）
```bash
export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
```

4. **重新加载环境变量**
```bash
source ~/.bashrc
```

5. **WSL2 特别注意**：如果在 WSL2 中运行，需要：
   - Windows 主机安装支持 CUDA 的 NVIDIA 驱动
   - WSL2 中安装 CUDA Toolkit（不需要驱动）
   - 参考：https://docs.nvidia.com/cuda/wsl-user-guide/

### 问题：如何检查 GPU 是否可用

```bash
# 检查 NVIDIA GPU
nvidia-smi

# 在程序中会自动检测
```

