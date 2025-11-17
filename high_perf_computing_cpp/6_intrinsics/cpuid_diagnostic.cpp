#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cpuid.h>

/**
 * CPUID 功能号 7 的正确调用方式诊断程序
 * 
 * 问题根源：功能号 7 需要 ECX 作为子功能号输入！
 */

void test_cpuid_function7() {
    std::cout << "=== CPUID 功能号 7 诊断程序 ===" << std::endl;
    std::cout << std::endl;

    // ============================================
    // 方法1：使用 __cpuid (错误的方式)
    // ============================================
    std::cout << "【方法1】使用 __cpuid(7, ...) - ❌ 错误" << std::endl;
    int cpuInfo1[4] = {0};
    __cpuid(7, cpuInfo1[0], cpuInfo1[1], cpuInfo1[2], cpuInfo1[3]);
    
    std::cout << "  EAX = 0x" << std::hex << std::setfill('0') << std::setw(8) << cpuInfo1[0] << std::endl;
    std::cout << "  EBX = 0x" << std::setw(8) << cpuInfo1[1] << std::endl;
    std::cout << "  ECX = 0x" << std::setw(8) << cpuInfo1[2] << std::endl;
    std::cout << "  EDX = 0x" << std::setw(8) << cpuInfo1[3] << std::endl;
    
    bool avx2_wrong = (cpuInfo1[1] & (1 << 5)) != 0;
    std::cout << "  AVX2 (bit 5): " << (avx2_wrong ? "✓" : "✗") << std::endl;
    std::cout << std::endl;
    
    std::cout << "  ⚠️ 问题：__cpuid() 没有设置 ECX = 0 作为子功能号！" << std::endl;
    std::cout << std::endl;

    // ============================================
    // 方法2：使用 __cpuid_count (正确的方式)
    // ============================================
    std::cout << "【方法2】使用 __cpuid_count(7, 0, ...) - ✓ 正确" << std::endl;
    int cpuInfo2[4] = {0};
    __cpuid_count(7, 0, cpuInfo2[0], cpuInfo2[1], cpuInfo2[2], cpuInfo2[3]);
    
    std::cout << "  EAX = 0x" << std::setw(8) << cpuInfo2[0] << std::endl;
    std::cout << "  EBX = 0x" << std::setw(8) << cpuInfo2[1] << std::endl;
    std::cout << "  ECX = 0x" << std::setw(8) << cpuInfo2[2] << std::endl;
    std::cout << "  EDX = 0x" << std::setw(8) << cpuInfo2[3] << std::endl;
    
    bool avx2_correct = (cpuInfo2[1] & (1 << 5)) != 0;
    std::cout << "  AVX2 (bit 5): " << (avx2_correct ? "✓" : "✗") << std::endl;
    std::cout << std::endl;

    // ============================================
    // 方法3：使用内联汇编 (正确的方式)
    // ============================================
    std::cout << "【方法3】使用内联汇编显式设置 ECX = 0 - ✓ 正确" << std::endl;
    uint32_t eax = 7, ebx = 0, ecx = 0, edx = 0;
    
    __asm__ __volatile__ (
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(eax), "c"(0)  // 重要：显式设置 ECX = 0
    );
    
    std::cout << "  EAX = 0x" << std::setw(8) << eax << std::endl;
    std::cout << "  EBX = 0x" << std::setw(8) << ebx << std::endl;
    std::cout << "  ECX = 0x" << std::setw(8) << ecx << std::endl;
    std::cout << "  EDX = 0x" << std::setw(8) << edx << std::endl;
    
    bool avx2_asm = (ebx & (1 << 5)) != 0;
    std::cout << "  AVX2 (bit 5): " << (avx2_asm ? "✓" : "✗") << std::endl;
    std::cout << std::endl;

    // ============================================
    // 详细分析 EBX 寄存器
    // ============================================
    std::cout << "=== EBX 寄存器位分析（功能号 7，子功能 0）===" << std::endl;
    std::cout << std::endl;
    
    uint32_t ebx_correct = cpuInfo2[1];
    
    std::cout << "EBX = 0x" << std::setw(8) << ebx_correct << std::endl;
    std::cout << "二进制: ";
    for (int i = 31; i >= 0; i--) {
        std::cout << ((ebx_correct >> i) & 1);
        if (i % 8 == 0 && i != 0) std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    
    struct Feature {
        int bit;
        const char* name;
    };
    
    Feature features[] = {
        {0, "FSGSBASE"},
        {3, "BMI1"},
        {5, "AVX2"},
        {8, "BMI2"},
        {16, "AVX512F"},
        {17, "AVX512DQ"},
        {21, "AVX512_IFMA"},
        {26, "AVX512PF"},
        {27, "AVX512ER"},
        {28, "AVX512CD"},
        {30, "AVX512BW"},
        {31, "AVX512VL"}
    };
    
    std::cout << "关键特性位：" << std::endl;
    for (const auto& f : features) {
        bool supported = (ebx_correct >> f.bit) & 1;
        std::cout << "  bit " << std::dec << std::setw(2) << f.bit << " - " 
                  << std::left << std::setw(15) << f.name 
                  << ": " << (supported ? "✓" : "✗") << std::endl;
    }
    std::cout << std::endl;

    // ============================================
    // 结论
    // ============================================
    std::cout << "=== 问题根源 ===" << std::endl;
    std::cout << std::endl;
    std::cout << "CPUID 功能号 7 是「结构化扩展功能」：" << std::endl;
    std::cout << "  • 输入：EAX = 7, ECX = 子功能号（通常为 0）" << std::endl;
    std::cout << "  • ECX 作为输入，指定要查询哪个子集" << std::endl;
    std::cout << std::endl;
    
    std::cout << "__cpuid(7, ...) 的问题：" << std::endl;
    std::cout << "  ❌ 只设置了 EAX = 7" << std::endl;
    std::cout << "  ❌ ECX 保持未初始化或之前的值" << std::endl;
    std::cout << "  ❌ 可能返回错误的结果" << std::endl;
    std::cout << std::endl;
    
    std::cout << "正确的做法：" << std::endl;
    std::cout << "  ✓ 使用 __cpuid_count(7, 0, ...) - C intrinsic" << std::endl;
    std::cout << "  ✓ 使用内联汇编显式设置 ECX = 0" << std::endl;
    std::cout << std::endl;
    
    // 比较结果
    if (cpuInfo1[1] != cpuInfo2[1]) {
        std::cout << "⚠️ 警告：两种方法的 EBX 值不同！" << std::endl;
        std::cout << "   __cpuid:       0x" << std::hex << std::setw(8) << cpuInfo1[1] << std::endl;
        std::cout << "   __cpuid_count: 0x" << std::setw(8) << cpuInfo2[1] << std::endl;
    } else {
        std::cout << "✓ 两种方法返回相同的 EBX 值" << std::endl;
    }
}

int main() {
    std::cout << std::hex << std::setfill('0');
    test_cpuid_function7();
    return 0;
}



