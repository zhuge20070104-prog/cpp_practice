# CPUID 功能号 7 的陷阱与正确用法

## 🐛 问题现象

你遇到的问题：

- **内联汇编版本** (`inline_asm`): AVX2 ✓ 支持
- **Intrinsics 版本** (`6_intrinsics`): AVX2 ✗ 不支持

同一台机器，不同结果！

## 🔍 问题根源

### CPUID 功能号分类

| 功能号类型 | 输入要求 | 示例 |
|-----------|---------|------|
| **简单功能号** | 只需要 EAX | 功能号 0, 1 |
| **复合功能号** | EAX + ECX（子功能号） | 功能号 7, 11, 13 |

### 功能号 7 的特殊性

功能号 7 是「**结构化扩展功能枚举**」：

```
输入：
  EAX = 7        （主功能号）
  ECX = 0        （子功能号，必须设置！）

输出：
  EAX = 最大支持的子功能号
  EBX = 扩展特性标志位（AVX2 在 bit 5）
  ECX = 更多扩展特性
  EDX = 更多扩展特性
```

## ❌ 错误的写法

### 问题代码

```cpp
// 6_intrinsics/main.cpp 原始代码
void get_cpu_id(int function_id, int cpuInfo[4]) {
    __cpuid(function_id, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
}

// 调用
get_cpu_id(7, cpuInfo);  // ❌ 问题：ECX 未初始化！
```

### 为什么出错？

```
__cpuid(7, ...) 实际执行：
  EAX = 7        ✓ 设置了
  ECX = ???      ❌ 未设置，保持之前的垃圾值！
  
CPUID 指令执行：
  如果 ECX != 0，可能返回：
    - 全 0（表示不支持该子功能）
    - 错误的数据
    - 未定义行为
```

## ✅ 正确的写法

### 方法1：使用 `__cpuid_count`（推荐）

```cpp
// 正确：显式指定子功能号
int cpuInfo[4] = {0};
__cpuid_count(7, 0, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
//            ↑  ↑
//            │  └── 子功能号（ECX = 0）
//            └───── 主功能号（EAX = 7）

bool avx2 = (cpuInfo[1] & (1 << 5)) != 0;
```

### 方法2：使用内联汇编（灵活）

```cpp
uint32_t eax = 7, ebx = 0, ecx = 0, edx = 0;

__asm__ __volatile__ (
    "cpuid"
    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    : "a"(7), "c"(0)  // ✓ 显式设置 EAX=7, ECX=0
);

bool avx2 = (ebx & (1 << 5)) != 0;
```

## 📊 两个版本的差异

### inline_asm 版本（正确）

```cpp
// 5_inline_assembly/main.cpp
eax = 7;
ecx = 0;  // ✓ 显式初始化

__asm__ __volatile__ (
    "cpuid"
    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    : "a"(eax), "c"(ecx)  // ✓ ECX = 0 作为输入
);
```

### 6_intrinsics 版本（原来是错误的）

```cpp
// 6_intrinsics/main.cpp (修复前)
void get_cpu_id(int function_id, int cpuInfo[4]) {
    __cpuid(function_id, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
    //      ↑ 只设置了 EAX，ECX 未设置！
}

get_cpu_id(7, cpuInfo);  // ❌ ECX 是垃圾值
```

## 🎓 深入理解：为什么内联汇编版本"碰巧"正确？

```cpp
// inline_asm 版本
eax = 7;
ecx = 0;  // 关键：显式赋值为 0

__asm__ __volatile__ (
    "cpuid"
    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    : "a"(eax), "c"(ecx)  // ECX 被正确传入
);
```

**关键点**：
- 代码显式写了 `ecx = 0`
- 内联汇编约束 `"c"(ecx)` 将这个 0 传给 ECX 寄存器
- 结果正确！

## 🔧 修复验证

### 修复后的代码

```cpp
// 6_intrinsics/main.cpp (修复后)
// 使用 __cpuid_count 代替 __cpuid
__cpuid_count(7, 0, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
bool avx2 = (cpuInfo[1] & (1 << 5)) != 0;
```

### 验证结果

重新编译运行：

```bash
cd 6_intrinsics/build
cmake --build .
./6_intrinsics
```

现在应该显示：
```
AVX2:   ✓  ← 修复后应该显示支持了！
```

## 📚 需要子功能号的其他 CPUID 功能

| 功能号 | 子功能号 (ECX) | 用途 |
|--------|---------------|------|
| **7** | 0, 1, 2 | 结构化扩展特性（AVX2, AVX-512等） |
| **11** | 0, 1, 2, ... | 扩展拓扑枚举 |
| **13** | 0, 1, 2, ... | 处理器扩展状态枚举（XSAVE） |
| **18** | 0, 1, 2, ... | TLB/Cache 信息 |

## 💡 最佳实践

### 1. 使用 Intrinsics 时

```cpp
// ✓ 对于需要子功能的，使用 __cpuid_count
__cpuid_count(7, 0, eax, ebx, ecx, edx);

// ✓ 对于简单功能号，可以用 __cpuid
__cpuid(1, eax, ebx, ecx, edx);
```

### 2. 使用内联汇编时

```cpp
// ✓ 总是显式设置所有输入寄存器
uint32_t eax = function_id;
uint32_t ecx = sub_function;  // 即使是 0 也要写！

__asm__ __volatile__ (
    "cpuid"
    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    : "a"(eax), "c"(ecx)  // 显式传入两个输入
);
```

### 3. 通用包装函数

```cpp
// 推荐的通用包装
void cpuid(uint32_t leaf, uint32_t subleaf, uint32_t* regs) {
    __cpuid_count(leaf, subleaf, regs[0], regs[1], regs[2], regs[3]);
}

// 使用
uint32_t regs[4];
cpuid(7, 0, regs);  // 清晰表达意图
```

## 🎯 总结

| 方面 | inline_asm 版本 | 6_intrinsics 版本（原） | 6_intrinsics 版本（修复） |
|------|----------------|---------------------|----------------------|
| ECX 设置 | ✓ `ecx = 0` | ❌ 未设置 | ✓ `__cpuid_count(7, 0, ...)` |
| AVX2 检测 | ✓ 正确 | ❌ 错误 | ✓ 正确 |
| 代码清晰度 | 中 | 低（隐藏了陷阱） | 高（意图明确） |

**教训**：
- CPUID 功能号 7 **必须**设置 ECX = 0 作为子功能号
- 使用 `__cpuid_count` 比 `__cpuid` 更安全、更明确
- 内联汇编需要程序员手动管理所有细节

🔗 **相关文档**：
- Intel SDM Volume 2: CPUID 指令详细说明
- GCC 文档: `__cpuid` 和 `__cpuid_count` 使用说明

