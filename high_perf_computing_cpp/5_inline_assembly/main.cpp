#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <bitset>

std::string get_cpu_name() {
    uint32_t data[4] = {0};

    __asm__ __volatile__ (
        "cpuid"
        : "=b"(data[0]), "=d"(data[1]), "=c"(data[2]), "=a"(data[3])
        : "a"(0)
    );

    return std::string((const char*)data, 12);
}

// CPU特性标志结构体
struct CPUFeatures {
    bool sse;              // SSE
    bool sse2;             // SSE2
    bool sse3;             // SSE3
    bool ssse3;            // SSSE3
    bool sse41;            // SSE4.1
    bool sse42;            // SSE4.2
    bool avx;              // AVX
    bool avx2;             // AVX2
    bool avx512f;          // AVX-512 Foundation
};


/**
 * 获取CPU支持的SIMD指令集
 * 
 * 原理说明：
 * CPUID指令是x86架构提供的CPU信息查询指令，通过不同的功能号（EAX输入）
 * 返回不同的CPU特性信息。
 * 
 * 1. CPUID功能号1（基本特性）：
 *    输入：EAX = 1
 *    输出：
 *      - ECX寄存器：扩展特性标志位
 *        bit 0:  SSE3
 *        bit 9:  SSSE3
 *        bit 19: SSE4.1
 *        bit 20: SSE4.2
 *        bit 28: AVX (操作系统也需要支持)
 *      - EDX寄存器：标准特性标志位
 *        bit 25: SSE
 *        bit 26: SSE2
 * 
 * 2. CPUID功能号7（结构化扩展特性）：
 *    输入：EAX = 7, ECX = 0
 *    输出：
 *      - EBX寄存器：扩展特性标志位
 *        bit 5:  AVX2
 *        bit 16: AVX-512F (Foundation)
 */
CPUFeatures get_cpu_simd_support() {
    CPUFeatures features = {false};
    uint32_t eax, ebx, ecx, edx;

    // ============================================
    // 第一步：查询基本特性（功能号 1）
    // ============================================
    eax = 1; // 功能号 1, 处理器信息和特性位
    ecx = 0;

    __asm__ __volatile__ (
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(eax), "c"(ecx)
    );

    // 注意X86 CPU是小端模式，低位在低字节，高位在高字节，所以这样移位
    // 解析EDX寄存器，标准特性
    features.sse = (edx >> 25) & 1;
    features.sse2 = (edx >> 26) & 1;

    // 解析ECX寄存器，扩展特性
    features.sse3 = (ecx >> 0) & 1;
    features.ssse3 = (ecx >> 9) & 1;
    features.sse41 = (ecx >> 19) & 1;
    features.sse42 = (ecx >> 20) & 1;
    features.avx = (ecx >> 28) & 1;

    // ============================================
    // 第二步：查询结构化扩展特性（功能号 7）
    // ============================================
    eax = 7; // 功能号 7, 结构化扩展特性
    ecx = 0;

    __asm__ __volatile__ (
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(eax), "c"(ecx)
    );

    // 解析EBX寄存器，结构化扩展特性
    features.avx2 = (ebx >> 5) & 1;
    features.avx512f = (ebx >> 16) & 1;

    return features;
}


// 显示CPU SIMD支持详情
void print_simd_support(const CPUFeatures& features) {
    std::cout << "\n=== CPU SIMD 指令集支持情况 ===" << std::endl;
    std::cout << std::left;
    
    std::cout << std::setw(15) << "指令集"
              << std::setw(10) << "支持"
              << std::setw(15) << "寄存器宽度"
              << "发布年份" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    auto print_status = [](const std::string& name, bool supported, 
                           const std::string& width, const std::string& year) {
        std::cout << std::setw(15) << name
                  << std::setw(10) << (supported ? "✓ 是" : "✗ 否")
                  << std::setw(15) << width
                  << year << std::endl;
    };

    print_status("SSE",     features.sse,     "128位 (XMM)", "1999");
    print_status("SSE2",    features.sse2,    "128位 (XMM)", "2001");
    print_status("SSE3",    features.sse3,    "128位 (XMM)", "2004");
    print_status("SSSE3",   features.ssse3,   "128位 (XMM)", "2006");
    print_status("SSE4.1",  features.sse41,   "128位 (XMM)", "2007");
    print_status("SSE4.2",  features.sse42,   "128位 (XMM)", "2008");
    print_status("AVX",     features.avx,     "256位 (YMM)", "2011");
    print_status("AVX2",    features.avx2,    "256位 (YMM)", "2013");
    print_status("AVX-512F", features.avx512f, "512位 (ZMM)", "2016");

    // 显示最高支持级别
    std::cout << "\n最高支持级别: ";
    if (features.avx512f) std::cout << "AVX-512" << std::endl;
    else if (features.avx2) std::cout << "AVX2" << std::endl;
    else if (features.avx) std::cout << "AVX" << std::endl;
    else if (features.sse42) std::cout << "SSE4.2" << std::endl;
    else if (features.sse41) std::cout << "SSE4.1" << std::endl;
    else if (features.ssse3) std::cout << "SSSE3" << std::endl;
    else if (features.sse3) std::cout << "SSE3" << std::endl;
    else if (features.sse2) std::cout << "SSE2" << std::endl;
    else if (features.sse) std::cout << "SSE" << std::endl;
    else std::cout << "无SIMD支持" << std::endl;
}

int main() {
    std::cout << "=== CPU 信息检测工具 ===" << std::endl;
    
    // 获取CPU厂商名称
    std::string cpu_name = get_cpu_name();
    std::cout << "\nCPU 厂商: " << cpu_name << std::endl;

    // 获取并显示SIMD支持
    CPUFeatures features = get_cpu_simd_support();
    print_simd_support(features);

    return 0;
}