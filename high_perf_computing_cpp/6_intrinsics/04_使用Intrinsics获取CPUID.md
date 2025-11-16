# 使用Intrinsics获取CPUID信息

## 什么是Intrinsics？

**Intrinsics**（内置函数）是编译器提供的**类似函数的接口**，用于访问底层的CPU指令，无需编写汇编代码。

### 优点

- ✅ **跨平台**：相同的代码在不同编译器中工作
- ✅ **类型安全**：编译器会检查类型
- ✅ **易于维护**：比汇编代码更易读
- ✅ **优化友好**：编译器可以更好地优化

### 三种方式对比

| 方式 | 难度 | 可移植性 | 性能 | 推荐度 |
|------|------|---------|------|--------|
| **内联汇编** | 高 | 低 | 高 | ⭐⭐ |
| **Intrinsics** | 中 | 高 | 高 | ⭐⭐⭐⭐⭐ |
| **编译器自动向量化** | 低 | 最高 | 中-高 | ⭐⭐⭐⭐ |

## CPUID指令简介

**CPUID** 是x86架构的特殊指令，用于获取CPU信息。

### CPUID的工作方式

```
输入：EAX寄存器 = 功能号
输出：EAX, EBX, ECX, EDX = 返回的信息
```

### 常用功能号

| EAX值 | 功能 | 返回值 |
|-------|------|--------|
| 0 | 获取厂商ID字符串 | EAX=最大功能号, EBX+EDX+ECX=厂商字符串 |
| 1 | 获取处理器信息和特性标志 | EAX=型号信息, ECX/EDX=功能位 |
| 2 | 获取缓存信息 | 描述符 |
| 7 | 扩展功能 | 高级CPU特性 |

## Windows vs Linux 差异

### Windows (MSVC)

```cpp
#include <intrin.h>

void get_cpuid(int function_id, int cpuInfo[4])
{
    __cpuid(cpuInfo, function_id);  // 结果直接存入数组
}
```

### Linux (GCC)

```cpp
#include <cpuid.h>

void get_cpuid(int function_id, int cpuInfo[4])
{
    __get_cpuid(function_id, 
                (unsigned int*)&cpuInfo[0], 
                (unsigned int*)&cpuInfo[1],
                (unsigned int*)&cpuInfo[2], 
                (unsigned int*)&cpuInfo[3]);
}
```

### 差异总结

- **MSVC**：`__cpuid(array, function_id)` - 数组在前
- **GCC**：`__get_cpuid(function_id, &eax, &ebx, &ecx, &edx)` - 需要指针

## 跨平台解决方案

### 方案1：条件编译封装 ⭐ 推荐

```cpp
#include <iostream>
#include <cstdint>
#include <string>
#include <cstring>

// 跨平台头文件
#ifdef _MSC_VER
    #include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
    #include <cpuid.h>
#endif

using namespace std;

// 跨平台CPUID wrapper
void get_cpuid(int function_id, int cpuInfo[4])
{
#ifdef _MSC_VER
    // Windows MSVC
    __cpuid(cpuInfo, function_id);
    
#elif defined(__GNUC__) || defined(__clang__)
    // Linux GCC/Clang
    __cpuid(function_id, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
    
#else
    #error "不支持的编译器"
#endif
}

// 获取CPU厂商字符串
string get_cpu_vendor()
{
    int cpuInfo[4] = {0};
    get_cpuid(0, cpuInfo);
    
    // cpuInfo[0] = EAX = 最大支持的功能号
    // cpuInfo[1] = EBX = 厂商字符串的前4个字符
    // cpuInfo[2] = ECX = 厂商字符串的后4个字符  
    // cpuInfo[3] = EDX = 厂商字符串的中4个字符
    
    // 重新排列：EBX + EDX + ECX
    char vendor[13] = {0};
    memcpy(vendor + 0, &cpuInfo[1], 4);  // EBX
    memcpy(vendor + 4, &cpuInfo[3], 4);  // EDX
    memcpy(vendor + 8, &cpuInfo[2], 4);  // ECX
    
    return string(vendor, 12);
}

// 获取CPU功能信息
void get_cpu_features()
{
    int cpuInfo[4] = {0};
    get_cpuid(1, cpuInfo);
    
    // cpuInfo[0] = EAX = 处理器信息和功能位
    // cpuInfo[1] = EBX = 其他功能信息
    // cpuInfo[2] = ECX = 功能标志位
    // cpuInfo[3] = EDX = 功能标志位
    
    cout << "处理器信息:" << endl;
    cout << "  EAX = 0x" << hex << cpuInfo[0] << endl;
    cout << "  EBX = 0x" << cpuInfo[1] << endl;
    cout << "  ECX = 0x" << cpuInfo[2] << endl;
    cout << "  EDX = 0x" << cpuInfo[3] << endl;
    cout << dec;
    
    // 检查SIMD支持（从EDX和ECX提取特定位）
    bool sse = (cpuInfo[3] & (1 << 25)) != 0;
    bool sse2 = (cpuInfo[3] & (1 << 26)) != 0;
    bool sse3 = (cpuInfo[2] & (1 << 0)) != 0;
    bool ssse3 = (cpuInfo[2] & (1 << 9)) != 0;
    bool sse41 = (cpuInfo[2] & (1 << 19)) != 0;
    bool sse42 = (cpuInfo[2] & (1 << 20)) != 0;
    bool avx = (cpuInfo[2] & (1 << 28)) != 0;
    
    cout << "\nSIMD 指令集支持:" << endl;
    cout << "  SSE:    " << (sse ? "✓" : "✗") << endl;
    cout << "  SSE2:   " << (sse2 ? "✓" : "✗") << endl;
    cout << "  SSE3:   " << (sse3 ? "✓" : "✗") << endl;
    cout << "  SSSE3:  " << (ssse3 ? "✓" : "✗") << endl;
    cout << "  SSE4.1: " << (sse41 ? "✓" : "✗") << endl;
    cout << "  SSE4.2: " << (sse42 ? "✓" : "✗") << endl;
    cout << "  AVX:    " << (avx ? "✓" : "✗") << endl;
}

void intrinsics()
{
    cout << "=== 使用 Intrinsics 获取 CPU 信息 ===" << endl;
    cout << "CPU 厂商: " << get_cpu_vendor() << endl;
    cout << endl;
    get_cpu_features();
}

int main(int argc, char* argv[])
{
    intrinsics();
    return 0;
}
```

## CPUID返回值详解

### 功能号 EAX=0：获取厂商字符串

```
输入：EAX = 0
输出：
  EAX = 最大支持的基本功能号
  EBX = 厂商ID的前4字符
  EDX = 厂商ID的中4字符
  ECX = 厂商ID的后4字符
```

**重要：组合顺序是 EBX + EDX + ECX，不是按字母顺序！**

#### 常见厂商字符串

| CPU厂商 | 返回字符串 | 说明 |
|---------|-----------|------|
| Intel | `GenuineIntel` | 最常见 |
| AMD | `AuthenticAMD` | AMD处理器 |
| VIA | `CentaurHauls` | 威盛处理器 |

#### 代码示例

```cpp
string get_cpu_vendor() {
    int cpuInfo[4];
    get_cpuid(0, cpuInfo);
    
    char vendor[13] = {0};
    // 注意顺序：EBX + EDX + ECX
    *((int*)vendor + 0) = cpuInfo[1];  // EBX
    *((int*)vendor + 1) = cpuInfo[3];  // EDX
    *((int*)vendor + 2) = cpuInfo[2];  // ECX
    
    return string(vendor);
}
```

### 功能号 EAX=1：获取处理器特性

```
输入：EAX = 1
输出：
  EAX = 处理器签名（型号、家族、步进）
  EBX = 品牌信息、CLFLUSH大小、逻辑CPU数
  ECX = 功能标志位（扩展特性）
  EDX = 功能标志位（基本特性）
```

#### EAX（处理器签名）解析

```
EAX位布局：
Bits 3-0:    Stepping ID（步进）
Bits 7-4:    Model（型号）
Bits 11-8:   Family（家族）
Bits 13-12:  Processor Type
Bits 19-16:  Extended Model
Bits 27-20:  Extended Family
```

```cpp
void parse_processor_signature(uint32_t eax) {
    int stepping = eax & 0xF;
    int model = (eax >> 4) & 0xF;
    int family = (eax >> 8) & 0xF;
    int type = (eax >> 12) & 0x3;
    int ext_model = (eax >> 16) & 0xF;
    int ext_family = (eax >> 20) & 0xFF;
    
    cout << "Stepping: " << stepping << endl;
    cout << "Model: " << model << endl;
    cout << "Family: " << family << endl;
}
```

#### ECX和EDX（功能标志位）

**EDX寄存器的关键位（基本特性）：**

| 位 | 特性 | 说明 |
|----|------|------|
| 0 | FPU | x87 FPU on chip |
| 4 | TSC | Time Stamp Counter |
| 15 | CMOV | 条件移动指令 |
| 23 | MMX | MMX指令集 |
| 25 | SSE | SSE指令集 |
| 26 | SSE2 | SSE2指令集 |

**ECX寄存器的关键位（扩展特性）：**

| 位 | 特性 | 说明 |
|----|------|------|
| 0 | SSE3 | SSE3指令集 |
| 9 | SSSE3 | SSSE3指令集 |
| 19 | SSE4.1 | SSE4.1指令集 |
| 20 | SSE4.2 | SSE4.2指令集 |
| 28 | AVX | AVX指令集 |
| 30 | RDRAND | 硬件随机数生成器 |

#### 检查特性代码

```cpp
bool check_feature(int reg, int bit) {
    return (reg & (1 << bit)) != 0;
}

void check_cpu_features() {
    int cpuInfo[4];
    get_cpuid(1, cpuInfo);
    
    int ecx = cpuInfo[2];
    int edx = cpuInfo[3];
    
    cout << "CPU 特性:" << endl;
    cout << "  MMX:    " << (check_feature(edx, 23) ? "✓" : "✗") << endl;
    cout << "  SSE:    " << (check_feature(edx, 25) ? "✓" : "✗") << endl;
    cout << "  SSE2:   " << (check_feature(edx, 26) ? "✓" : "✗") << endl;
    cout << "  SSE3:   " << (check_feature(ecx, 0) ? "✓" : "✗") << endl;
    cout << "  SSSE3:  " << (check_feature(ecx, 9) ? "✓" : "✗") << endl;
    cout << "  SSE4.1: " << (check_feature(ecx, 19) ? "✓" : "✗") << endl;
    cout << "  SSE4.2: " << (check_feature(ecx, 20) ? "✓" : "✗") << endl;
    cout << "  AVX:    " << (check_feature(ecx, 28) ? "✓" : "✗") << endl;
}
```

## 面向对象封装

更优雅的做法是封装成类：

```cpp
#include <iostream>
#include <cstring>
#include <cstdint>

#ifdef _MSC_VER
    #include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
    #include <cpuid.h>
#endif

using namespace std;

class CPUInfo {
private:
    int registers[4];
    
public:
    // 执行CPUID指令
    void execute(int function_id) {
#ifdef _MSC_VER
        __cpuid(registers, function_id);
#elif defined(__GNUC__) || defined(__clang__)
        __cpuid(function_id, registers[0], registers[1], 
                registers[2], registers[3]);
#else
        // 回退到内联汇编
        asm volatile(
            "cpuid"
            : "=a"(registers[0]), "=b"(registers[1]),
              "=c"(registers[2]), "=d"(registers[3])
            : "a"(function_id)
        );
#endif
    }
    
    // 访问各个寄存器
    int eax() const { return registers[0]; }
    int ebx() const { return registers[1]; }
    int ecx() const { return registers[2]; }
    int edx() const { return registers[3]; }
    
    // 获取厂商字符串
    string getVendor() {
        execute(0);
        char vendor[13] = {0};
        memcpy(vendor + 0, &registers[1], 4);  // EBX
        memcpy(vendor + 4, &registers[3], 4);  // EDX
        memcpy(vendor + 8, &registers[2], 4);  // ECX
        return string(vendor, 12);
    }
    
    // 获取品牌字符串（需要多次CPUID调用）
    string getBrand() {
        char brand[49] = {0};
        int* ptr = (int*)brand;
        
        for (int i = 0; i < 3; i++) {
            execute(0x80000002 + i);
            ptr[i * 4 + 0] = registers[0];
            ptr[i * 4 + 1] = registers[1];
            ptr[i * 4 + 2] = registers[2];
            ptr[i * 4 + 3] = registers[3];
        }
        
        return string(brand);
    }
    
    // 检查指定特性
    bool hasFeature(int reg_index, int bit) {
        execute(1);
        return (registers[reg_index] & (1 << bit)) != 0;
    }
    
    // 便捷方法
    bool hasSSE()   { return hasFeature(3, 25); }
    bool hasSSE2()  { return hasFeature(3, 26); }
    bool hasSSE3()  { return hasFeature(2, 0); }
    bool hasSSE41() { return hasFeature(2, 19); }
    bool hasSSE42() { return hasFeature(2, 20); }
    bool hasAVX()   { return hasFeature(2, 28); }
    bool hasAVX2() {
        execute(7);
        return (registers[1] & (1 << 5)) != 0;
    }
    
    // 打印所有信息
    void printInfo() {
        cout << "CPU厂商: " << getVendor() << endl;
        cout << "CPU品牌: " << getBrand() << endl;
        cout << "\nSIMD支持:" << endl;
        cout << "  SSE:    " << (hasSSE() ? "✓" : "✗") << endl;
        cout << "  SSE2:   " << (hasSSE2() ? "✓" : "✗") << endl;
        cout << "  SSE3:   " << (hasSSE3() ? "✓" : "✗") << endl;
        cout << "  SSE4.1: " << (hasSSE41() ? "✓" : "✗") << endl;
        cout << "  SSE4.2: " << (hasSSE42() ? "✓" : "✗") << endl;
        cout << "  AVX:    " << (hasAVX() ? "✓" : "✗") << endl;
        cout << "  AVX2:   " << (hasAVX2() ? "✓" : "✗") << endl;
    }
};

int main() {
    CPUInfo cpu;
    cpu.printInfo();
    
    // 也可以单独查询
    if (cpu.hasAVX()) {
        cout << "\n你的CPU支持AVX，可以使用256位SIMD！" << endl;
    }
    
    return 0;
}
```

## 使用Intrinsics处理SIMD数据

除了获取CPUID，Intrinsics更常用于SIMD编程：

```cpp
#include <xmmintrin.h>  // SSE
#include <immintrin.h>  // AVX

void intrinsics_example() {
    // 使用_mm_set_ps设置数据
    // 注意：参数顺序是反的！
    __m128 a = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);  // 实际存储为 [4,3,2,1]
    __m128 b = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);  // 实际存储为 [1,2,3,4]
    
    // SIMD加法
    __m128 c = _mm_add_ps(a, b);  // [5,5,5,5]
    
    // 提取结果
    alignas(16) float result[4];
    _mm_store_ps(result, c);
    
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
```

## 编译命令

### Linux/WSL (GCC)

```bash
# 基本编译
g++ -o cpuid_test cpuid_test.cpp -std=c++11

# 带优化
g++ -O3 -o cpuid_test cpuid_test.cpp -std=c++11

# 使用SSE指令
g++ -O3 -msse -o cpuid_test cpuid_test.cpp -std=c++11

# 使用本机所有指令集
g++ -O3 -march=native -o cpuid_test cpuid_test.cpp -std=c++11
```

### Windows (MSVC)

```bash
# 基本编译
cl /EHsc cpuid_test.cpp

# 带优化
cl /O2 /EHsc cpuid_test.cpp

# 使用AVX
cl /arch:AVX /O2 cpuid_test.cpp
```

## 预期输出示例

```
=== 使用 Intrinsics 获取 CPU 信息 ===
CPU 厂商: GenuineIntel
CPU品牌: Intel(R) Core(TM) i7-9700K CPU @ 3.60GHz

处理器信息:
  EAX = 0x906ea
  EBX = 0x2100800
  ECX = 0x7ffafbbf
  EDX = 0xbfebfbff

SIMD 指令集支持:
  SSE:    ✓
  SSE2:   ✓
  SSE3:   ✓
  SSSE3:  ✓
  SSE4.1: ✓
  SSE4.2: ✓
  AVX:    ✓
  AVX2:   ✓

你的CPU支持AVX，可以使用256位SIMD！
```

## 常用Intrinsics函数速查

### CPUID相关

| 平台 | 函数 | 说明 |
|------|------|------|
| MSVC | `__cpuid(int*, int)` | 执行CPUID |
| GCC | `__get_cpuid(uint, uint*, uint*, uint*, uint*)` | 执行CPUID |
| GCC | `__get_cpuid_count(uint, uint, uint*, ...)` | 带子功能号 |

### SSE Intrinsics（128位）

| 函数 | 说明 |
|------|------|
| `_mm_set_ps(d,c,b,a)` | 设置4个float（倒序） |
| `_mm_setr_ps(a,b,c,d)` | 设置4个float（正序） |
| `_mm_load_ps(ptr)` | 加载对齐的数据 |
| `_mm_loadu_ps(ptr)` | 加载未对齐的数据 |
| `_mm_store_ps(ptr, v)` | 存储对齐的数据 |
| `_mm_add_ps(a, b)` | 加法 |
| `_mm_mul_ps(a, b)` | 乘法 |

### AVX Intrinsics（256位）

| 函数 | 说明 |
|------|------|
| `_mm256_set_ps(...)` | 设置8个float |
| `_mm256_load_ps(ptr)` | 加载数据 |
| `_mm256_add_ps(a, b)` | 加法 |
| `_mm256_mul_ps(a, b)` | 乘法 |

## 总结

### 跨平台CPUID的要点

✅ **MSVC和GCC的API不同，需要条件编译**  
✅ **厂商字符串的组合顺序是 EBX+EDX+ECX**  
✅ **功能位分布在ECX和EDX寄存器中**  
✅ **封装成类更易用**  

### Intrinsics的优势

✅ **比内联汇编更易移植**  
✅ **类型安全，编译器检查**  
✅ **性能接近汇编**  
✅ **代码更易读易维护**  

## 参考资料

- [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- [CPUID Wikipedia](https://en.wikipedia.org/wiki/CPUID)
- [Sandpile CPUID Info](https://www.sandpile.org/x86/cpuid.htm)

