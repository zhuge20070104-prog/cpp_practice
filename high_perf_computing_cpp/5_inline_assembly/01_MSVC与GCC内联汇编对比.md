# MSVC与GCC内联汇编对比

## 概述

内联汇编在不同编译器中的语法完全不同，本文档对比MSVC (Windows)和GCC (Linux)的差异。

## 平台兼容性

| 特性 | MSVC (Windows) | GCC (Linux) |
|------|----------------|-------------|
| 内联汇编语法 | `__asm { ... }` | `__asm__(...)` 或 `asm(...)` |
| 汇编风格 | Intel 语法 | AT&T 语法（默认） |
| 输入输出约束 | 不需要 | 需要明确指定 |
| 寄存器前缀 | 无（`eax`, `xmm0`） | 需要（`%eax`, `%xmm0`） |

## 示例对比

### MSVC (Windows) 版本

```cpp
#include "stdafx.h"
#include <string>
#include <cstdint>

std::string get_cpu_name()
{
    uint32_t data[4] = { 0 };
    
    // MSVC 内联汇编
    __asm
    {
        cpuid;
        mov data[0], ebx;
        mov data[4], edx;
        mov data[8], ecx;
    }
    
    return std::string((const char*)data);
}

int main(int argc, char* argv[])
{
    getchar();
    return 0;
}
```

**特点：**
- 使用 `__asm { ... }` 块
- Intel 语法（目标在前，源在后）
- 可以直接访问C++变量
- 不需要指定输入输出约束

### GCC (Linux/WSL) 版本

```cpp
#include <string>
#include <cstdint>

std::string get_cpu_name()
{
    uint32_t data[4] = { 0 };
    
    // GCC 内联汇编
    __asm__ __volatile__(
        "cpuid"
        : "=b"(data[0]), "=d"(data[1]), "=c"(data[2])
        : "a"(0)
        : "eax"
    );
    
    return std::string((const char*)data);
}

int main(int argc, char* argv[])
{
    std::string cpu_name = get_cpu_name();
    return 0;
}
```

**特点：**
- 使用 `__asm__ __volatile__(...)` 
- AT&T 语法（源在前，目标在后）
- 需要明确指定输入输出操作数
- 需要列出被破坏的寄存器

## SSE SIMD 示例对比

### MSVC 版本

```cpp
void assembler()
{
    cout << "CPU is " << get_cpu_name() << endl;
    
    float f1[] = { 1.f, 2.f, 3.f, 4.f };
    float f2[] = { 5.f, 4.f, 3.f, 2.f };
    float result[4] = { 0.f };
    
    __asm
    {
        movups xmm1, f1;        // 加载f1到xmm1
        movups xmm2, f2;        // 加载f2到xmm2
        mulps xmm1, xmm2;       // xmm1 = xmm1 * xmm2
        movups result, xmm1;    // 保存结果
    }
}
```

### GCC 版本 (AT&T语法)

```cpp
void assembler()
{
    cout << "CPU is " << get_cpu_name() << endl;
    
    alignas(16) float f1[] = { 1.f, 2.f, 3.f, 4.f };
    alignas(16) float f2[] = { 5.f, 4.f, 3.f, 2.f };
    alignas(16) float result[4] = { 0.f };
    
    // AT&T 语法（操作数顺序相反）
    __asm__ __volatile__(
        "movups (%1), %%xmm1\n\t"      // 从f1加载到xmm1
        "movups (%2), %%xmm2\n\t"      // 从f2加载到xmm2
        "mulps %%xmm2, %%xmm1\n\t"     // xmm1 = xmm1 * xmm2
        "movups %%xmm1, (%0)\n\t"      // 保存xmm1到result
        :                               // 输出操作数
        : "r"(result), "r"(f1), "r"(f2) // 输入操作数
        : "%xmm1", "%xmm2", "memory"    // 破坏描述符
    );
}
```

### GCC 版本 (Intel语法)

```cpp
void assembler()
{
    alignas(16) float f1[] = { 1.f, 2.f, 3.f, 4.f };
    alignas(16) float f2[] = { 5.f, 4.f, 3.f, 2.f };
    alignas(16) float result[4] = { 0.f };
    
    // 强制使用Intel语法
    __asm__ __volatile__(
        ".intel_syntax noprefix\n\t"
        "movups xmm1, [%1]\n\t"
        "movups xmm2, [%2]\n\t"
        "mulps xmm1, xmm2\n\t"
        "movups [%0], xmm1\n\t"
        ".att_syntax prefix\n\t"
        :
        : "r"(result), "r"(f1), "r"(f2)
        : "%xmm1", "%xmm2", "memory"
    );
}
```

## AT&T vs Intel 语法对比

| 特性 | Intel (MSVC) | AT&T (GCC默认) |
|------|--------------|----------------|
| 操作数顺序 | `mov dest, src` | `mov src, dest` |
| 寄存器前缀 | `xmm1` | `%xmm1` |
| 立即数前缀 | `5` | `$5` |
| 内存访问 | `[eax]` | `(%eax)` |
| 指令后缀 | 无 | 有（`movl`, `movq`） |

### 示例对比

```asm
# Intel 语法
mov eax, 5
mov eax, [ebx]
add eax, ecx

# AT&T 语法  
movl $5, %eax
movl (%ebx), %eax
addl %ecx, %eax
```

## 编译命令

### Linux/WSL (GCC)

```bash
# 基本编译
g++ -o program program.cpp -msse -std=c++11

# 启用AVX
g++ -o program program.cpp -mavx -std=c++11

# 启用所有本机支持的指令
g++ -o program program.cpp -march=native -std=c++11
```

### Windows (MSVC)

```bash
# 基本编译
cl /EHsc program.cpp

# 启用AVX
cl /arch:AVX program.cpp

# 启用AVX2
cl /arch:AVX2 program.cpp
```

## 关键差异总结

### MSVC特点
- ✅ 语法简单，直观
- ✅ 直接访问变量
- ❌ 只能在Windows上使用
- ❌ 64位程序不支持内联汇编

### GCC特点
- ✅ 跨平台（Linux、macOS、Windows MinGW）
- ✅ 支持32位和64位
- ✅ 更精确的寄存器控制
- ❌ 语法复杂，学习曲线陡峭

## 移植建议

如果要编写跨平台的汇编代码，建议：

1. **使用条件编译**
```cpp
#ifdef _MSC_VER
    // MSVC 代码
    __asm {
        // ...
    }
#elif defined(__GNUC__) || defined(__clang__)
    // GCC/Clang 代码
    __asm__ __volatile__(
        // ...
    );
#endif
```

2. **优先使用Intrinsics**（下一章介绍）
```cpp
#include <xmmintrin.h>  // 跨平台的SSE函数
__m128 a = _mm_load_ps(data);
```

3. **让编译器自动向量化**
```cpp
// 简单代码，编译器会自动优化
for (int i = 0; i < n; i++) {
    c[i] = a[i] + b[i];
}
```

## 注意事项

1. **内存对齐**：SSE指令通常需要16字节对齐
```cpp
alignas(16) float data[4];  // C++11对齐
```

2. **volatile关键字**：防止编译器优化掉汇编代码
```cpp
__asm__ __volatile__(...)  // 不要优化这段代码
```

3. **寄存器破坏列表**：告诉编译器哪些寄存器被修改了
```cpp
: "%xmm1", "%xmm2", "memory"  // xmm1、xmm2和内存被修改
```

## 参考资料

- [GCC Extended Asm文档](https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html)
- [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- [x86 Assembly Guide](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html)

