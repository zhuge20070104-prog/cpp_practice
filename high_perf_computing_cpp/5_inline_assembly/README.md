# 内联汇编与SIMD编程指南

本目录包含了关于内联汇编、SIMD指令集和编译器向量化的完整教程。

## 📚 文档目录

### [01 - MSVC与GCC内联汇编对比](./01_MSVC与GCC内联汇编对比.md)
- Windows (MSVC) 和 Linux (GCC) 的内联汇编语法差异
- Intel语法 vs AT&T语法
- SSE SIMD代码的跨平台实现
- 编译命令对比
- 移植建议和最佳实践

**适合：** 需要编写跨平台内联汇编代码的开发者

---

### [02 - GCC内联汇编语法详解](./02_GCC内联汇编语法详解.md)
- GCC扩展汇编的完整语法
- `__asm__ __volatile__` 详解
- 输入输出操作数约束
- 寄存器约束符号（a, b, c, d, r等）
- 破坏描述符（Clobbers）
- AT&T vs Intel语法
- 实用示例和调试技巧

**适合：** 深入学习GCC内联汇编的开发者

---

### [03 - SSE与SIMD技术详解](./03_SSE与SIMD技术详解.md)
- SIMD（单指令多数据）原理
- SSE指令集详解
- XMM寄存器详解（128位）
- SSE常用指令（movps, addps, mulps等）
- SSE发展历史（SSE → SSE2 → SSE3 → SSE4 → AVX）
- Packed vs Scalar操作
- 内存对齐要求
- 性能对比和应用场景

**适合：** 想要理解SIMD技术原理的开发者

---

### [04 - 使用Intrinsics获取CPUID](./04_使用Intrinsics获取CPUID.md)
- 什么是Intrinsics（内置函数）
- CPUID指令详解
- Windows vs Linux的API差异
- 跨平台CPUID封装
- 获取CPU厂商字符串
- 检测CPU特性（SSE、AVX等）
- 面向对象封装示例
- 完整的CPUInfo类实现

**适合：** 需要检测CPU特性或使用Intrinsics的开发者

---

### [05 - 编译器自动向量化详解](./05_编译器自动向量化详解.md)
- 编译器自动向量化原理
- GCC、Clang、Intel ICC对比
- 向量化报告详解（`-fopt-info-vec`）
- 容易向量化 vs 难以向量化的代码特征
- 查看生成的汇编代码
- 性能对比（自动向量化 vs 手动SIMD）
- 向量化辅助指令（pragma）
- 最佳实践和编译命令

**适合：** 想要让编译器自动优化代码的开发者

---

## 🚀 快速开始

### 编译环境

#### Linux/WSL (GCC)
```bash
# 基本编译
g++ -o program program.cpp -msse -std=c++11

# 开启优化和向量化
g++ -O3 -march=native -o program program.cpp

# 查看向量化报告
g++ -O3 -march=native -o program program.cpp -fopt-info-vec-all
```

#### Windows (MSVC)
```bash
# 基本编译
cl /EHsc program.cpp

# 开启优化
cl /O2 /arch:AVX2 program.cpp

# 查看向量化报告
cl /O2 /arch:AVX2 /Qvec-report:2 program.cpp
```

### Hello SIMD

```cpp
#include <iostream>
#include <xmmintrin.h>  // SSE

int main() {
    // 使用Intrinsics
    alignas(16) float a[4] = {1, 2, 3, 4};
    alignas(16) float b[4] = {5, 6, 7, 8};
    alignas(16) float c[4];
    
    __m128 va = _mm_load_ps(a);
    __m128 vb = _mm_load_ps(b);
    __m128 vc = _mm_add_ps(va, vb);  // 4个加法同时完成！
    _mm_store_ps(c, vc);
    
    std::cout << "Result: ";
    for (int i = 0; i < 4; i++) {
        std::cout << c[i] << " ";  // 6 8 10 12
    }
    std::cout << std::endl;
    
    return 0;
}
```

编译运行：
```bash
g++ -O3 -march=native -o hello_simd hello_simd.cpp
./hello_simd
```

## 📊 性能对比

| 方式 | 难度 | 可移植性 | 性能 | 推荐度 |
|------|------|---------|------|--------|
| **编译器自动向量化** | ⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| **Intrinsics** | ⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ |
| **内联汇编** | ⭐⭐⭐⭐⭐ | ⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐ |

### 建议

1. **首选编译器自动向量化**
   - 简单的循环让编译器自动优化
   - 使用 `-O3 -march=native`

2. **需要精确控制时使用Intrinsics**
   - 跨平台兼容性好
   - 性能接近汇编
   - 代码可读性强

3. **极少数情况使用内联汇编**
   - 需要特殊指令
   - 极致性能调优
   - 难以维护

## 🔧 常用工具

### 查看CPU支持的指令集

```bash
# Linux
cat /proc/cpuinfo | grep -i sse
lscpu | grep -i flags

# 输出示例
flags: sse sse2 sse3 ssse3 sse4_1 sse4_2 avx avx2
```

### 查看生成的汇编代码

```bash
# GCC
g++ -O3 -march=native -S -masm=intel -o output.s program.cpp

# 查找SIMD指令
cat output.s | grep -E "(addps|mulps|movaps|xmm|ymm)"
```

### 性能分析

```bash
# 使用perf
g++ -O3 -march=native -g -o program program.cpp
perf stat ./program
perf record ./program
perf report

# 使用valgrind
valgrind --tool=cachegrind ./program
```

## 📖 学习路线

### 初级（1-2周）
1. ✅ 阅读 [03 - SSE与SIMD技术详解](./03_SSE与SIMD技术详解.md)
2. ✅ 理解SIMD的基本概念
3. ✅ 学习 [05 - 编译器自动向量化详解](./05_编译器自动向量化详解.md)
4. ✅ 编写简单的循环，让编译器自动向量化

### 中级（2-3周）
1. ✅ 学习 [04 - 使用Intrinsics获取CPUID](./04_使用Intrinsics获取CPUID.md)
2. ✅ 使用SSE Intrinsics重写简单算法
3. ✅ 学习AVX指令集（256位）
4. ✅ 优化实际项目中的性能热点

### 高级（1-2个月）
1. ✅ 学习 [01 - MSVC与GCC内联汇编对比](./01_MSVC与GCC内联汇编对比.md)
2. ✅ 学习 [02 - GCC内联汇编语法详解](./02_GCC内联汇编语法详解.md)
3. ✅ 编写跨平台的SIMD代码
4. ✅ 深入理解CPU微架构
5. ✅ 学习AVX-512（如果CPU支持）

## 🎯 实战项目

### 项目1：向量运算库
- 实现向量加法、减法、乘法、点积
- 对比标量版本 vs SIMD版本的性能
- 支持float和double

### 项目2：图像处理
- 实现图像模糊（高斯模糊）
- 实现色彩空间转换（RGB↔YUV）
- 使用SIMD加速

### 项目3：矩阵乘法
- 实现朴素矩阵乘法
- 使用SIMD优化
- 使用分块优化缓存
- 对比性能提升

### 项目4：CPU特性检测工具
- 检测CPU厂商和型号
- 列出支持的指令集
- 测试各种SIMD指令的性能

## 📚 参考资料

### 官方文档
- [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html) - 最权威的Intrinsics参考
- [GCC Extended Asm](https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html) - GCC内联汇编官方文档
- [GCC Vectorization](https://gcc.gnu.org/projects/tree-ssa/vectorization.html) - GCC向量化文档

### 优化手册
- [Agner Fog's Optimization Manuals](https://www.agner.org/optimize/) - 必读的优化圣经
- [Intel 64 and IA-32 Architectures Optimization Reference Manual](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-optimization-manual.html)

### 在线工具
- [Compiler Explorer](https://godbolt.org/) - 在线查看编译结果
- [Quick Bench](https://quick-bench.com/) - 在线性能测试

### 书籍推荐
- 《Computer Systems: A Programmer's Perspective》- 深入理解计算机系统
- 《Optimizing Software in C++》- C++优化技术
- 《What Every Programmer Should Know About Memory》

## 🤝 贡献

欢迎提出问题和改进建议！

## 📝 许可

本教程仅供学习参考使用。

---

**最后更新：** 2025年11月15日

