# GCC内联汇编语法详解

## 基本格式

GCC扩展汇编的标准格式：

```cpp
__asm__ [volatile] (
    "汇编指令"          // 汇编代码
    : 输出操作数列表    // 第1个冒号
    : 输入操作数列表    // 第2个冒号
    : 破坏描述符列表    // 第3个冒号
);
```

## 关键字说明

### `__asm__` 或 `asm`

- **`__asm__`**：GCC的内联汇编关键字（推荐，避免命名冲突）
- **`asm`**：简写形式（可能与某些代码冲突）

### `__volatile__` 或 `volatile`

- 告诉编译器**不要优化这段汇编代码**
- 防止编译器重排序、删除或合并这段代码
- 当汇编代码有副作用时必须使用

```cpp
__asm__ __volatile__(...)  // 推荐写法
__asm__ volatile(...)      // 也可以
```

## 完整示例解析

让我们逐行解释一个实际的例子：

```cpp
__asm__ __volatile__(
    "cpuid"
    : "=b"(data[0]), "=d"(data[1]), "=c"(data[2])
    : "a"(0)
    : "eax"
);
```

### 第1行：`__asm__ __volatile__(`

- **`__asm__`**：内联汇编关键字
- **`__volatile__`**：防止编译器优化
  - 因为 `cpuid` 有副作用（读取CPU信息），编译器可能无法理解

### 第2行：`"cpuid"`

- 实际要执行的**汇编指令**
- **`cpuid`**：x86的CPU识别指令
  - 读取 `eax` 寄存器的值作为功能号
  - 将结果写入 `eax`, `ebx`, `ecx`, `edx` 四个寄存器

### 第3行：`: "=b"(data[0]), "=d"(data[1]), "=c"(data[2])`

这是**输出操作数列表**（Output Operands）

#### `"=b"(data[0])`
- **`=`**：表示"只写"（这是一个输出）
- **`b`**：表示使用 **`ebx`** 寄存器
- **`(data[0])`**：将 `ebx` 的值写入到 `data[0]` 变量中

#### `"=d"(data[1])`
- **`=`**：只写
- **`d`**：表示使用 **`edx`** 寄存器
- **`(data[1])`**：将 `edx` 的值写入到 `data[1]` 中

#### `"=c"(data[2])`
- **`=`**：只写
- **`c`**：表示使用 **`ecx`** 寄存器
- **`(data[2])`**：将 `ecx` 的值写入到 `data[2]` 中

### 第4行：`: "a"(0)`

这是**输入操作数列表**（Input Operands）

#### `"a"(0)`
- **`a`**：表示使用 **`eax`** 寄存器
- **`(0)`**：在执行 `cpuid` 之前，将值 `0` 放入 `eax` 寄存器
- `eax=0` 表示查询CPU厂商ID字符串

### 第5行：`: "eax"`

这是**破坏描述符列表**（Clobber List）

- 告诉编译器 `eax` 寄存器被修改了
- 这样编译器就不会假设 `eax` 的值在汇编代码后保持不变
- 对于 `cpuid`，`eax` 会被修改，所以必须声明

**更完整的写法应该是：**

```cpp
__asm__ __volatile__(
    "cpuid"
    : "=a"(data_eax), "=b"(data[0]), "=d"(data[1]), "=c"(data[2])
    : "a"(0)
    :  // 如果所有被修改的寄存器都在输出列表，就不需要额外声明
);
```

## 寄存器约束符号

### 常用寄存器约束

| 约束符 | 32位寄存器 | 64位寄存器 | 说明 |
|--------|-----------|-----------|------|
| `a` | eax | rax | 累加器 |
| `b` | ebx | rbx | 基址寄存器 |
| `c` | ecx | rcx | 计数器 |
| `d` | edx | rdx | 数据寄存器 |
| `S` | esi | rsi | 源索引 |
| `D` | edi | rdi | 目的索引 |
| `r` | 任意 | 任意 | 让编译器选择 |

### SSE/AVX寄存器

```cpp
"x" - 任意 XMM 寄存器 (xmm0-xmm15)
```

示例：
```cpp
__asm__ volatile(
    "addps %1, %0"
    : "+x"(result)   // xmm寄存器，读写
    : "x"(value)     // xmm寄存器，只读
);
```

## 操作数修饰符

### 输出修饰符

| 修饰符 | 含义 | 示例 |
|--------|------|------|
| `=` | 只写（输出） | `"=r"(output)` |
| `+` | 读写（输入输出） | `"+r"(value)` |
| `&` | early clobber（提前破坏） | `"=&r"(temp)` |

### 示例

```cpp
int a = 5, b = 10, result;

// 只输出
__asm__("addl %%ebx, %%eax"
    : "=a"(result)      // eax 只写
    : "a"(a), "b"(b)    // eax=a, ebx=b
);

// 读写（累加）
__asm__("addl %1, %0"
    : "+r"(a)           // a = a + b
    : "r"(b)
);
```

## 内存操作数

### 使用 `m` 约束

```cpp
int value = 10;
__asm__("incl %0"       // 直接对内存操作
    : "+m"(value)       // 内存操作数
);
```

### 使用寄存器间接寻址

```cpp
float arr[4] = {1, 2, 3, 4};

__asm__(
    "movups (%0), %%xmm0"
    :
    : "r"(arr)          // 传入指针
    : "%xmm0"
);
```

## 操作数编号

在汇编指令中，使用 `%0`, `%1`, `%2` 等引用操作数：

```cpp
int a = 5, b = 10, c = 0;

__asm__(
    "addl %2, %1\n\t"     // b = b + a
    "movl %1, %0"         // c = b
    : "=r"(c)             // %0 = c (输出)
    : "r"(b), "r"(a)      // %1 = b, %2 = a (输入)
);
```

**注意：** 输出和输入按顺序编号，从0开始。

## 破坏描述符（Clobbers）

告诉编译器哪些资源被修改了：

### 寄存器破坏

```cpp
: "eax", "ebx", "ecx"   // 这些寄存器被修改了
```

### 内存破坏

```cpp
: "memory"              // 内存被修改（防止编译器缓存内存值）
```

### 条件码破坏

```cpp
: "cc"                  // 条件码寄存器（EFLAGS）被修改
```

### 完整示例

```cpp
__asm__ __volatile__(
    "cpuid"
    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
    : "a"(function_id)
    : "cc"              // EFLAGS被修改
);
```

## 多条指令

使用 `\n\t` 分隔多条指令：

```cpp
__asm__ __volatile__(
    "movl %1, %%eax\n\t"
    "addl %2, %%eax\n\t"
    "movl %%eax, %0\n\t"
    : "=r"(result)
    : "r"(a), "r"(b)
    : "%eax"
);
```

**为什么用 `\n\t`？**
- `\n`：换行，让生成的汇编代码更可读
- `\t`：制表符，汇编器可能需要

## AT&T 语法要点

GCC默认使用AT&T语法：

### 1. 寄存器前缀 `%`

```asm
movl %eax, %ebx     # ebx = eax
```

**在内联汇编中要用 `%%`：**

```cpp
__asm__("movl %%eax, %%ebx");
```

因为单个 `%` 用于引用操作数（`%0`, `%1`）。

### 2. 立即数前缀 `$`

```asm
movl $5, %eax       # eax = 5
```

### 3. 操作数顺序：源在前，目标在后

```asm
addl %ebx, %eax     # eax = eax + ebx（目标是eax）
```

### 4. 内存访问

```asm
movl (%eax), %ebx   # ebx = *eax
movl 4(%eax), %ebx  # ebx = *(eax + 4)
```

### 5. 指令后缀

| 后缀 | 含义 | 大小 |
|------|------|------|
| `b` | byte | 8位 |
| `w` | word | 16位 |
| `l` | long | 32位 |
| `q` | quad | 64位 |

```asm
movb $1, %al        # 移动1字节
movw $1, %ax        # 移动2字节
movl $1, %eax       # 移动4字节
movq $1, %rax       # 移动8字节
```

## 切换到Intel语法

如果你更喜欢Intel语法：

```cpp
__asm__ __volatile__(
    ".intel_syntax noprefix\n\t"
    "mov eax, 5\n\t"
    "add eax, ebx\n\t"
    ".att_syntax prefix\n\t"
    :
    :
    : "eax"
);
```

## 实用示例

### 示例1：读取时间戳计数器（RDTSC）

```cpp
uint64_t read_tsc() {
    uint32_t lo, hi;
    __asm__ __volatile__(
        "rdtsc"
        : "=a"(lo), "=d"(hi)
    );
    return ((uint64_t)hi << 32) | lo;
}
```

### 示例2：原子交换

```cpp
int atomic_exchange(int* ptr, int new_value) {
    int old_value;
    __asm__ __volatile__(
        "xchgl %0, %1"
        : "=r"(old_value), "+m"(*ptr)
        : "0"(new_value)
        : "memory"
    );
    return old_value;
}
```

### 示例3：SSE加法

```cpp
void sse_add(float* a, float* b, float* result) {
    __asm__ __volatile__(
        "movups (%1), %%xmm0\n\t"
        "movups (%2), %%xmm1\n\t"
        "addps %%xmm1, %%xmm0\n\t"
        "movups %%xmm0, (%0)"
        :
        : "r"(result), "r"(a), "r"(b)
        : "%xmm0", "%xmm1", "memory"
    );
}
```

## 常见错误

### ❌ 错误1：忘记 `%%` 前缀

```cpp
// 错误
__asm__("movl %eax, %ebx");  // 编译器会找 %eax 操作数

// 正确
__asm__("movl %%eax, %%ebx");
```

### ❌ 错误2：忘记声明破坏的寄存器

```cpp
// 错误：eax被修改但没声明
__asm__("movl $5, %%eax" : : : );

// 正确
__asm__("movl $5, %%eax" : : : "eax");
```

### ❌ 错误3：内存对齐问题

```cpp
// 错误：SSE需要16字节对齐
float data[4];
__asm__("movaps %%xmm0, %0" : "=m"(data));

// 正确
alignas(16) float data[4];
__asm__("movaps %%xmm0, %0" : "=m"(data));
```

## 调试技巧

### 查看生成的汇编代码

```bash
g++ -S -o output.s source.cpp
cat output.s
```

### 查看内联汇编展开

```bash
g++ -O2 -S -masm=intel -o output.s source.cpp
```

### 查看预处理后的代码

```bash
g++ -E source.cpp | less
```

## 最佳实践

1. **优先使用Intrinsics**：更安全，可移植
2. **使用 `__volatile__`**：防止意外优化
3. **明确指定破坏列表**：避免神秘bug
4. **添加注释**：汇编代码难读，多加注释
5. **测试不同优化级别**：`-O0`, `-O2`, `-O3`

## 参考资料

- [GCC Inline Assembly HOWTO](https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html)
- [GCC Extended Asm](https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html)
- [Linux Kernel内联汇编](https://www.kernel.org/doc/html/latest/asm-annotations.html)

