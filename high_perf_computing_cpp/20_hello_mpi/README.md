# Intel MPI + Boost.MPI 安装与配置指南

本项目使用 **Intel MPI** 作为底层 MPI 实现，并使用 **Boost.MPI** 提供 C++ 友好的接口。

---

## 📦 安装步骤（Ubuntu/WSL）

### 步骤1：添加 Intel oneAPI 仓库

```bash
# 下载并添加 Intel GPG 密钥
wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB \
| gpg --dearmor | sudo tee /usr/share/keyrings/oneapi-archive-keyring.gpg > /dev/null

# 添加 Intel oneAPI 仓库
echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" \
| sudo tee /etc/apt/sources.list.d/oneAPI.list

# 更新包列表
sudo apt update
```

### 步骤2：安装 Intel MPI

```bash
# 安装 Intel MPI 运行时和开发包
sudo apt install -y intel-oneapi-mpi-devel

# 查看安装位置
ls /opt/intel/oneapi/mpi/
```

**安装大小**：约 500 MB  
**安装时间**：3-5 分钟

### 步骤3：安装 Boost.MPI

```bash
# 安装 Boost.MPI 和序列化库
sudo apt install -y \
    libboost-mpi-dev \
    libboost-serialization-dev

# 验证安装
dpkg -l | grep libboost-mpi
```

### 步骤4：配置环境变量

Intel MPI 需要设置环境变量才能使用：

```bash
# 临时生效（当前终端）
source /opt/intel/oneapi/setvars.sh

# 永久生效（添加到 ~/.bashrc）
echo 'source /opt/intel/oneapi/setvars.sh --force' >> ~/.bashrc
source ~/.bashrc
```

---

## ✅ 验证安装

### 检查 Intel MPI

```bash
# 1. 检查 mpirun 版本
mpirun --version
# 输出应包含 "Intel(R) MPI Library"

# 2. 检查编译器
which mpicxx
# 输出：/opt/intel/oneapi/mpi/latest/bin/mpicxx

# 3. 查看 Intel MPI 信息
ls /opt/intel/oneapi/mpi/latest/
```

### 检查 Boost.MPI

```bash
# 1. 检查头文件
ls /usr/include/boost/mpi.hpp

# 2. 检查库文件
ls /usr/lib/x86_64-linux-gnu/libboost_mpi.so*

# 3. 查看版本
dpkg -l | grep libboost-mpi
```

---

## 🔧 编译和运行

### 方法1：使用 CMake（推荐）

```bash
# 创建构建目录
mkdir build && cd build

# 配置（确保已 source setvars.sh）
cmake ..

# 编译
make

# 运行（4个进程）
mpirun -np 4 ./20_hello_mpi
```

### 方法2：手动编译

```bash
# 使用 Intel MPI 的 mpicxx 编译器
mpicxx main.cpp -lboost_mpi -lboost_serialization -o hello_mpi

# 运行
mpirun -np 4 ./hello_mpi
```

---

## 📝 快速测试

### 创建简单的 Boost.MPI 程序

```cpp
#include <boost/mpi.hpp>
#include <iostream>
namespace mpi = boost::mpi;

int main(int argc, char** argv) {
    mpi::environment env(argc, argv);
    mpi::communicator world;
    
    std::cout << "Hello from rank " << world.rank() 
              << " of " << world.size() 
              << " (Intel MPI + Boost.MPI)" << std::endl;
    
    // 简单的通信测试
    if (world.rank() == 0) {
        int data = 42;
        world.send(1, 0, data);
        std::cout << "Rank 0 sent: " << data << std::endl;
    } else if (world.rank() == 1) {
        int data;
        world.recv(0, 0, data);
        std::cout << "Rank 1 received: " << data << std::endl;
    }
    
    return 0;
}
```

---

## 🎯 Intel MPI vs OpenMPI

### 为什么选择 Intel MPI？

| 特性 | Intel MPI | OpenMPI |
|------|-----------|---------|
| **Intel CPU 优化** | ✅ 优化 | ❌ 通用 |
| **性能** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ |
| **安装大小** | 较大 (~500MB) | 较小 (~100MB) |
| **许可证** | 免费（Intel License） | BSD（开源） |
| **WSL 支持** | ✅ 支持 | ✅ 支持 |
| **文档** | Intel 官方文档 | 社区文档 |

### 性能对比（参考）

在 Intel CPU 上：
- Intel MPI：通常有 5-15% 性能提升
- 特别是在大规模通信时优势明显

---

## 🔄 切换 MPI 实现

如果您想在 Intel MPI 和 OpenMPI 之间切换：

### 使用 Intel MPI

```bash
source /opt/intel/oneapi/setvars.sh
which mpirun
# 输出：/opt/intel/oneapi/mpi/.../bin/mpirun
```

### 切换到 OpenMPI

```bash
# 1. 安装 OpenMPI
sudo apt install openmpi-bin libopenmpi-dev

# 2. 修改 PATH（临时）
export PATH=/usr/bin:$PATH

# 3. 验证
which mpirun
# 输出：/usr/bin/mpirun
```

---

## ⚙️ 环境变量说明

### Intel MPI 关键环境变量

```bash
# setvars.sh 会设置这些变量：
export I_MPI_ROOT=/opt/intel/oneapi/mpi/latest
export PATH=$I_MPI_ROOT/bin:$PATH
export LD_LIBRARY_PATH=$I_MPI_ROOT/lib:$LD_LIBRARY_PATH
export MANPATH=$I_MPI_ROOT/man:$MANPATH
```

### 常用 Intel MPI 环境变量

```bash
# 指定网络接口（避免 WSL 网络问题）
export I_MPI_FABRICS=shm        # 只使用共享内存

# 调试信息
export I_MPI_DEBUG=5            # 显示详细调试信息

# 线程亲和性
export I_MPI_PIN=1              # 启用线程绑定
```

---

## 🛠️ 常见问题

### 问题1：找不到 mpirun

```bash
# 解决：确保已 source
source /opt/intel/oneapi/setvars.sh

# 或检查路径
which mpirun
```

### 问题2：编译时找不到 Boost.MPI

```bash
# 解决：手动指定库路径
mpicxx main.cpp \
    -I/usr/include \
    -L/usr/lib/x86_64-linux-gnu \
    -lboost_mpi -lboost_serialization \
    -o hello_mpi
```

### 问题3：运行时错误 "Dapl startup: RLIMIT_MEMLOCK too small"

```bash
# 这是 Intel MPI 在 WSL 中的常见警告
# 解决：使用共享内存模式
export I_MPI_FABRICS=shm
mpirun -np 4 ./hello_mpi
```

### 问题4：Boost.MPI 链接到错误的 MPI

```bash
# 检查 Boost.MPI 链接的 MPI 实现
ldd /usr/lib/x86_64-linux-gnu/libboost_mpi.so | grep mpi

# 如果链接到 OpenMPI，但您想用 Intel MPI：
# 这是正常的！Boost.MPI 运行时会使用当前 PATH 中的 MPI
# 只要 PATH 中 Intel MPI 在前面即可
```

---

## 📚 参考资源

### Intel MPI 文档

- **官方文档**: https://www.intel.com/content/www/us/en/docs/mpi-library/
- **开发者指南**: https://www.intel.com/content/www/us/en/developer/tools/oneapi/mpi-library.html
- **性能调优**: https://www.intel.com/content/www/us/en/docs/mpi-library/developer-guide-linux/

### Boost.MPI 文档

- **官方文档**: https://www.boost.org/doc/libs/1_74_0/doc/html/mpi.html
- **教程**: https://www.boost.org/doc/libs/1_74_0/doc/html/mpi/tutorial.html

---

## 🎊 快速开始总结

```bash
# 1. 一键安装脚本
wget -O- https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB \
| gpg --dearmor | sudo tee /usr/share/keyrings/oneapi-archive-keyring.gpg > /dev/null

echo "deb [signed-by=/usr/share/keyrings/oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" \
| sudo tee /etc/apt/sources.list.d/oneAPI.list

sudo apt update
sudo apt install -y intel-oneapi-mpi-devel libboost-mpi-dev libboost-serialization-dev

# 2. 配置环境
echo 'source /opt/intel/oneapi/setvars.sh --force' >> ~/.bashrc
source ~/.bashrc

# 3. 验证
mpirun --version

# 4. 编译运行
cd build
cmake ..
make
mpirun -np 4 ./20_hello_mpi
```

---

## 📊 性能提示

### 最佳实践

1. **使用共享内存** - WSL 环境推荐
   ```bash
   export I_MPI_FABRICS=shm
   ```

2. **线程绑定** - 提升性能
   ```bash
   export I_MPI_PIN=1
   export I_MPI_PIN_PROCESSOR_LIST=0-7
   ```

3. **进程数量** - 不要超过 CPU 核心数
   ```bash
   # 查看 CPU 核心数
   nproc
   
   # 使用合适的进程数
   mpirun -np $(nproc) ./20_hello_mpi
   ```

---

**最后更新**: 2025-11-16  
**环境**: WSL2 Ubuntu 22.04 + Intel oneAPI 2024  
**Boost 版本**: 1.74.0

