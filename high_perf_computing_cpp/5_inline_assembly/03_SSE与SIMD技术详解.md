# SSE与SIMD技术详解

## 什么是SIMD？

**SIMD** = **Single Instruction, Multiple Data**（单指令多数据）

一种并行计算架构，允许一条指令同时处理多个数据。

## SIMD的核心概念

### 传统串行计算 vs SIMD并行计算

**传统方式（串行）：**
```cpp
// 需要4次乘法操作
c[0] = a[0] * b[0];  // 第1次
c[1] = a[1] * b[1];  // 第2次
c[2] = a[2] * b[2];  // 第3次
c[3] = a[3] * b[3];  // 第4次
```

**SIMD方式（并行）：**
```cpp
// 只需1次乘法操作！
[c[0], c[1], c[2], c[3]] = [a[0], a[1], a[2], a[3]] * [b[0], b[1], b[2], b[3]]
```

### 性能提升

```
理论加速比 = 一次处理的数据量
- SSE: 4个float → 4倍加速
- AVX: 8个float → 8倍加速
- AVX-512: 16个float → 16倍加速
```

## 什么是SSE？

**SSE** = **Streaming SIMD Extensions**（流式单指令多数据扩展）

Intel在1999年推出的x86 CPU指令集扩展，用于实现并行计算。

## SSE寄存器

SSE引入了新的寄存器：**XMM寄存器**

### 寄存器特性

- 数量：xmm0 ~ xmm15（64位模式）
- 大小：每个寄存器 **128位**（16字节）
- 可以存储：
  - **4个** 32位浮点数 (float)
  - **2个** 64位浮点数 (double)
  - **16个** 8位整数 (char)
  - **8个** 16位整数 (short)
  - **4个** 32位整数 (int)
  - **2个** 64位整数 (long long)

### XMM寄存器图示

```
XMM1 寄存器 (128位)
┌────────┬────────┬────────┬────────┐
│ 1.0f   │ 2.0f   │ 3.0f   │ 4.0f   │  ← 4个float (单精度)
└────────┴────────┴────────┴────────┘
  32位     32位     32位     32位

XMM2 寄存器 (128位)
┌────────────────┬────────────────┐
│     1.0        │     2.0        │  ← 2个double (双精度)
└────────────────┴────────────────┘
     64位              64位
```

## SSE代码示例

### 示例：4个浮点数同时相乘

```cpp
#include <iostream>
using namespace std;

void assembler()
{
    // SSE要求16字节对齐
    alignas(16) float f1[] = { 1.f, 2.f, 3.f, 4.f };
    alignas(16) float f2[] = { 5.f, 4.f, 3.f, 2.f };
    alignas(16) float result[4] = { 0.f };
    
    // GCC内联汇编 - AT&T语法
    __asm__ __volatile__(
        "movups (%1), %%xmm1\n\t"      // 将f1加载到xmm1
        "movups (%2), %%xmm2\n\t"      // 将f2加载到xmm2
        "mulps %%xmm2, %%xmm1\n\t"     // xmm1 = xmm1 * xmm2（4个乘法同时完成！）
        "movups %%xmm1, (%0)\n\t"      // 保存xmm1到result
        :                               // 输出操作数
        : "r"(result), "r"(f1), "r"(f2) // 输入操作数
        : "%xmm1", "%xmm2", "memory"    // 破坏描述符
    );
    
    // 打印结果
    cout << "Result: ";
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";  // 输出: 5 8 9 8
    }
    cout << endl;
}

int main()
{
    assembler();
    return 0;
}
```

**执行过程：**
```
f1:      [1.0, 2.0, 3.0, 4.0]
f2:      [5.0, 4.0, 3.0, 2.0]
         ↓  一条mulps指令  ↓
result:  [5.0, 8.0, 9.0, 8.0]
```

**计算：**
- result[0] = 1.0 × 5.0 = 5.0
- result[1] = 2.0 × 4.0 = 8.0
- result[2] = 3.0 × 3.0 = 9.0
- result[3] = 4.0 × 2.0 = 8.0

## SSE常用指令

### 数据传送指令

| 指令 | 含义 | 说明 |
|------|------|------|
| `movaps` | MOVe Aligned Packed Single | 移动对齐的打包单精度浮点数 |
| `movups` | MOVe Unaligned Packed Single | 移动未对齐的打包单精度浮点数 |
| `movapd` | MOVe Aligned Packed Double | 移动对齐的打包双精度浮点数 |
| `movupd` | MOVe Unaligned Packed Double | 移动未对齐的打包双精度浮点数 |

**对齐 vs 未对齐：**
- `movaps` 要求数据16字节对齐，速度更快
- `movups` 不要求对齐，但可能稍慢

### 算术运算指令

| 指令 | 含义 | 操作 |
|------|------|------|
| `addps` | ADD Packed Single | 4个float加法 |
| `subps` | SUBtract Packed Single | 4个float减法 |
| `mulps` | MULtiply Packed Single | 4个float乘法 |
| `divps` | DIVide Packed Single | 4个float除法 |
| `addpd` | ADD Packed Double | 2个double加法 |
| `mulpd` | MULtiply Packed Double | 2个double乘法 |

### 逻辑运算指令

| 指令 | 含义 | 操作 |
|------|------|------|
| `andps` | AND Packed Single | 按位与 |
| `orps` | OR Packed Single | 按位或 |
| `xorps` | XOR Packed Single | 按位异或 |
| `andnps` | AND NOT Packed Single | 按位与非 |

### 比较指令

| 指令 | 含义 |
|------|------|
| `cmpps` | CoMPare Packed Single |
| `maxps` | MAXimum Packed Single |
| `minps` | MINimum Packed Single |

## SSE发展历史

| 版本 | 年份 | 代表CPU | 寄存器 | 主要特性 |
|------|------|---------|--------|----------|
| **MMX** | 1997 | Pentium MMX | MM0-MM7 (64位) | 整数SIMD |
| **SSE** | 1999 | Pentium III | XMM0-XMM7 (128位) | 单精度浮点，8个寄存器 |
| **SSE2** | 2001 | Pentium 4 | XMM0-XMM7 | 双精度浮点，整数运算 |
| **SSE3** | 2004 | Pentium 4 | XMM0-XMM7 | 增强水平运算 |
| **SSSE3** | 2006 | Core 2 | XMM0-XMM7 | 补充SSE3 |
| **SSE4.1** | 2007 | Core 2 | XMM0-XMM7 | 视频处理优化 |
| **SSE4.2** | 2008 | Core i7 | XMM0-XMM15 (64位模式) | 字符串处理，16个寄存器 |
| **AVX** | 2011 | Sandy Bridge | YMM0-YMM15 (256位) | 8个float |
| **AVX2** | 2013 | Haswell | YMM0-YMM15 | 整数支持 |
| **AVX-512** | 2016 | Xeon Phi / Skylake-X | ZMM0-ZMM31 (512位) | 16个float，32个寄存器 |

## Packed vs Scalar

### Packed（打包）操作

一次处理所有元素：

```asm
; addps: 4个加法同时执行
xmm0 = [1, 2, 3, 4]
xmm1 = [5, 6, 7, 8]
addps xmm0, xmm1
xmm0 = [6, 8, 10, 12]
```

### Scalar（标量）操作

只处理最低位的一个元素：

```asm
; addss: 只有第一个元素相加
xmm0 = [1, 2, 3, 4]
xmm1 = [5, 6, 7, 8]
addss xmm0, xmm1
xmm0 = [6, 2, 3, 4]  ← 只有第一个元素改变
```

| 后缀 | 含义 | 操作数量 |
|------|------|---------|
| `ps` | Packed Single | 4个float |
| `pd` | Packed Double | 2个double |
| `ss` | Scalar Single | 1个float |
| `sd` | Scalar Double | 1个double |

## Packaged Single Float Data

**"Packaged Single Float Data"** 的含义：

- **Packaged** = 打包的、紧凑排列的
- **Single** = 单精度（32位float）
- **Float** = 浮点数
- **Data** = 数据

**完整含义：** 把多个单精度浮点数打包在一起，用SIMD指令一次性处理。

### 示例

```cpp
// 普通处理：一次1个float
float a = 1.0f, b = 2.0f, c;
c = a * b;  // 1个乘法

// 打包处理：一次4个float
__m128 va = {1.0f, 2.0f, 3.0f, 4.0f};  // 打包4个float
__m128 vb = {5.0f, 4.0f, 3.0f, 2.0f};
__m128 vc = _mm_mul_ps(va, vb);        // 4个乘法同时完成！
```

## SSE应用场景

### 1. 图形处理

```cpp
// 同时处理4个像素的RGBA值
struct Pixel {
    float r, g, b, a;
};

// 用SSE一次处理
__m128 pixel1 = _mm_load_ps(&p1.r);
__m128 pixel2 = _mm_load_ps(&p2.r);
__m128 blended = _mm_add_ps(
    _mm_mul_ps(pixel1, alpha),
    _mm_mul_ps(pixel2, one_minus_alpha)
);
```

### 2. 科学计算

```cpp
// 向量点积
float dot_product(float* a, float* b, int n) {
    __m128 sum = _mm_setzero_ps();
    for (int i = 0; i < n; i += 4) {
        __m128 va = _mm_load_ps(&a[i]);
        __m128 vb = _mm_load_ps(&b[i]);
        sum = _mm_add_ps(sum, _mm_mul_ps(va, vb));
    }
    // 水平相加
    // ...
}
```

### 3. 音视频处理

```cpp
// 批量音频样本处理
void apply_gain(float* samples, float gain, int count) {
    __m128 vgain = _mm_set1_ps(gain);  // 广播gain到4个元素
    for (int i = 0; i < count; i += 4) {
        __m128 vsample = _mm_loadu_ps(&samples[i]);
        vsample = _mm_mul_ps(vsample, vgain);
        _mm_storeu_ps(&samples[i], vsample);
    }
}
```

### 4. 机器学习

```cpp
// 矩阵乘法的一部分
// C[i][j] = sum(A[i][k] * B[k][j])
```

## 性能对比示例

```cpp
#include <iostream>
#include <chrono>
#include <xmmintrin.h>

const int N = 10000000;

// 普通循环
void scalar_multiply(float* a, float* b, float* c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * b[i];
    }
}

// SSE版本
void sse_multiply(float* a, float* b, float* c, int n) {
    for (int i = 0; i < n; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        __m128 vc = _mm_mul_ps(va, vb);
        _mm_storeu_ps(&c[i], vc);
    }
}

int main() {
    float* a = new float[N];
    float* b = new float[N];
    float* c = new float[N];
    
    for (int i = 0; i < N; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }
    
    // 测试标量版本
    auto start = std::chrono::high_resolution_clock::now();
    scalar_multiply(a, b, c, N);
    auto end = std::chrono::high_resolution_clock::now();
    auto scalar_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // 测试SSE版本
    start = std::chrono::high_resolution_clock::now();
    sse_multiply(a, b, c, N);
    end = std::chrono::high_resolution_clock::now();
    auto sse_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "标量版本: " << scalar_time.count() << " ms" << std::endl;
    std::cout << "SSE版本:  " << sse_time.count() << " ms" << std::endl;
    std::cout << "加速比:   " << (float)scalar_time.count() / sse_time.count() << "x" << std::endl;
    
    delete[] a;
    delete[] b;
    delete[] c;
    
    return 0;
}
```

**典型输出：**
```
标量版本: 25 ms
SSE版本:  7 ms
加速比:   3.57x
```

## 内存对齐

SSE指令对内存对齐有要求：

### 为什么需要对齐？

- **对齐的数据**：访问速度更快
- **未对齐的数据**：可能需要多次内存访问

### 对齐方法

```cpp
// C++11 方式
alignas(16) float data[4];

// C 方式
float* data = (float*)aligned_alloc(16, size * sizeof(float));

// POSIX 方式
float* data;
posix_memalign((void**)&data, 16, size * sizeof(float));

// 检查是否对齐
bool is_aligned = ((uintptr_t)data % 16) == 0;
```

### 对齐 vs 未对齐指令

```cpp
// 对齐版本（更快，但要求16字节对齐）
movaps xmm0, [rax]   # 如果未对齐会崩溃！
_mm_load_ps(ptr)

// 未对齐版本（稍慢，但安全）
movups xmm0, [rax]   # 任何地址都可以
_mm_loadu_ps(ptr)
```

## 检查CPU支持

### 运行时检查

```cpp
#include <cpuid.h>

bool check_sse_support() {
    unsigned int eax, ebx, ecx, edx;
    __get_cpuid(1, &eax, &ebx, &ecx, &edx);
    
    bool sse = (edx & (1 << 25)) != 0;
    bool sse2 = (edx & (1 << 26)) != 0;
    bool sse3 = (ecx & (1 << 0)) != 0;
    bool sse41 = (ecx & (1 << 19)) != 0;
    bool sse42 = (ecx & (1 << 20)) != 0;
    bool avx = (ecx & (1 << 28)) != 0;
    
    return sse;  // 或其他版本
}
```

### 命令行检查

```bash
# Linux
cat /proc/cpuinfo | grep -i sse
# 输出: sse sse2 sse3 ssse3 sse4_1 sse4_2 ...

# 或者
lscpu | grep -i flags
```

## 编译选项

```bash
# 启用SSE
g++ -msse program.cpp

# 启用SSE2
g++ -msse2 program.cpp

# 启用SSE4.1
g++ -msse4.1 program.cpp

# 启用所有本机支持的指令
g++ -march=native program.cpp

# 针对特定CPU优化
g++ -march=skylake program.cpp
```

## 总结

| 特性 | 说明 |
|------|------|
| **SSE** | Intel的SIMD指令集扩展 |
| **XMM寄存器** | 128位寄存器（xmm0-xmm15） |
| **一次处理** | 4个float 或 2个double |
| **理论加速** | 最高4倍（实际2-3倍） |
| **对齐要求** | 推荐16字节对齐 |
| **适用场景** | 图形、科学计算、音视频、AI |

### 关键要点

✅ **SSE让CPU一次处理4个float，显著提升性能**  
✅ **XMM寄存器是128位，可以存储多种数据类型**  
✅ **"Packaged Single Float Data" = 打包的单精度浮点数据**  
✅ **现代CPU普遍支持SSE，甚至AVX/AVX2**  
✅ **内存对齐可以提升性能**  

## 下一步

- 学习 Intrinsics（SSE的C++封装）
- 学习 AVX（256位，8个float）
- 学习编译器自动向量化
- 实践：优化实际应用

## 参考资料

- [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- [SSE Wikipedia](https://en.wikipedia.org/wiki/Streaming_SIMD_Extensions)
- [Agner Fog's Optimization Manuals](https://www.agner.org/optimize/)

