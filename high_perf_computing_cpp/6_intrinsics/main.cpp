#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <bitset>
#include <cpuid.h>
#include <cstring>
#include <xmmintrin.h>  // SSE
#include <immintrin.h>  // AVX

/**
 * 统一的 CPUID 查询函数
 * 
 * @param leaf      功能号（EAX 输入）
 * @param subleaf   子功能号（ECX 输入），默认为 0
 * @param cpuInfo   输出数组 [EAX, EBX, ECX, EDX]
 * 
 * 说明：
 * - 使用 __cpuid_count 可以处理所有 CPUID 功能号
 * - 对于简单功能号（如 0, 1），subleaf 设为 0 即可（会被忽略）
 * - 对于复合功能号（如 7, 11, 13），必须正确设置 subleaf
 * - 比 __cpuid 更安全、更通用
 */
inline void cpuid(uint32_t leaf, uint32_t subleaf, uint32_t cpuInfo[4]) {
    __cpuid_count(leaf, subleaf, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
}

// CPU 特性标志结构体
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

// 获取CPU厂商字符串
std::string get_cpu_vendor() {
    uint32_t cpuInfo[4] = {0};
    cpuid(0, 0,  cpuInfo); 

    // cpuInfo[0] = EAX = 最大支持的功能号
    // cpuInfo[1] = EBX = 厂商字符串的前4个字符
    // cpuInfo[2] = ECX = 厂商字符串的后4个字符  
    // cpuInfo[3] = EDX = 厂商字符串的中4个字符
    
    // 重新排列： EBX + EDX + ECX
    char vendor[13] = {0};
    std::memcpy(vendor + 0, &cpuInfo[1], 4);
    std::memcpy(vendor + 4, &cpuInfo[3], 4);
    std::memcpy(vendor + 8, &cpuInfo[2], 4);
    return std::string(vendor, 12);
}


/**
 * 获取 CPU 支持的 SIMD 指令集特性
 * 
 * 原理说明：
 * CPUID 指令是 x86 架构提供的 CPU 信息查询指令，通过不同的功能号（EAX 输入）
 * 返回不同的 CPU 特性信息。
 * 
 * 1. CPUID 功能号 1（基本特性）：
 *    输入：EAX = 1
 *    输出：
 *      - ECX 寄存器：扩展特性标志位
 *        bit 0:  SSE3
 *        bit 9:  SSSE3
 *        bit 19: SSE4.1
 *        bit 20: SSE4.2
 *        bit 28: AVX (操作系统也需要支持)
 *      - EDX 寄存器：标准特性标志位
 *        bit 25: SSE
 *        bit 26: SSE2
 * 
 * 2. CPUID 功能号 7（结构化扩展特性）：
 *    输入：EAX = 7, ECX = 0
 *    输出：
 *      - EBX 寄存器：扩展特性标志位
 *        bit 5:  AVX2
 *        bit 16: AVX-512F (Foundation)
 * 
 * @return CPUFeatures 结构体，包含所有 SIMD 指令集的支持情况
 */
CPUFeatures get_cpu_features() {
    CPUFeatures features = {false};
    uint32_t cpuInfo[4] = {0};
    
    // ============================================
    // 功能号 1：基本处理器信息和特性位
    // ============================================
    cpuid(1, 0, cpuInfo); 

    // cpuInfo[0] = EAX = 处理器签名（型号、家族等）
    // cpuInfo[1] = EBX = 其他功能信息
    // cpuInfo[2] = ECX = 扩展特性标志位
    // cpuInfo[3] = EDX = 标准特性标志位

    // 从 EDX 提取 SSE/SSE2
    features.sse = (cpuInfo[3] & (1 << 25)) != 0;
    features.sse2 = (cpuInfo[3] & (1 << 26)) != 0;
    
    // 从 ECX 提取 SSE3 到 AVX
    features.sse3 = (cpuInfo[2] & (1 << 0)) != 0;
    features.ssse3 = (cpuInfo[2] & (1 << 9)) != 0;
    features.sse41 = (cpuInfo[2] & (1 << 19)) != 0;
    features.sse42 = (cpuInfo[2] & (1 << 20)) != 0;
    features.avx = (cpuInfo[2] & (1 << 28)) != 0;

    // ============================================
    // 功能号 7，子功能号 0：结构化扩展特性
    // ============================================
    cpuid(7, 0, cpuInfo);  // 显式指定子功能号 0
    
    // cpuInfo[0] = EAX = 最大支持的子功能号
    // cpuInfo[1] = EBX = 扩展特性标志位（AVX2, AVX-512等）
    // cpuInfo[2] = ECX = 更多扩展特性
    // cpuInfo[3] = EDX = 更多扩展特性

    features.avx2 = (cpuInfo[1] & (1 << 5)) != 0;
    features.avx512f = (cpuInfo[1] & (1 << 16)) != 0;

    return features;
}

// 打印 CPU SIMD 支持信息
void print_cpu_features(const CPUFeatures& features) {
    std::cout << "\nSIMD 指令集支持:" << std::endl;
    std::cout << "  SSE:      " << (features.sse ? "✓" : "✗") << std::endl;
    std::cout << "  SSE2:     " << (features.sse2 ? "✓" : "✗") << std::endl;
    std::cout << "  SSE3:     " << (features.sse3 ? "✓" : "✗") << std::endl;
    std::cout << "  SSSE3:    " << (features.ssse3 ? "✓" : "✗") << std::endl;
    std::cout << "  SSE4.1:   " << (features.sse41 ? "✓" : "✗") << std::endl;
    std::cout << "  SSE4.2:   " << (features.sse42 ? "✓" : "✗") << std::endl;
    std::cout << "  AVX:      " << (features.avx ? "✓" : "✗") << std::endl;
    std::cout << "  AVX2:     " << (features.avx2 ? "✓" : "✗") << std::endl;
    std::cout << "  AVX-512F: " << (features.avx512f ? "✓" : "✗") << std::endl;
}


// 显示 CPU 信息并返回特性结构体
CPUFeatures get_cpu_info() {
    std::cout << "\nCPU 信息:" << std::endl;
    std::cout << "  厂商: " << get_cpu_vendor() << std::endl;
    
    CPUFeatures features = get_cpu_features();
    print_cpu_features(features);
    
    return features;
}


void intrinsics_example(const CPUFeatures& features) {
    std::cout << "\n=== Intrinsics 示例 ===" << std::endl;
    
    // SSE 示例 (128位，4个float)
    std::cout << "\n[SSE] 128位向量加法 (4个float):" << std::endl;
    __m128 a = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);  // 实际存储为 [4,3,2,1]
    __m128 b = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);  // 实际存储为 [1,2,3,4]
    // SIMD 加法
    __m128 c = _mm_add_ps(a, b);  // 实际存储为 [5,5,5,5]
    alignas(16) float result[4];
    _mm_store_ps(result, c);
    std::cout << "结果: ";
    for(int i=0; i<4; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    // AVX 示例 - 运行前检查 CPU 支持
    if (features.avx) {
        std::cout << "\n[AVX] 256位向量加法 (4个double):" << std::endl;
        __m256d z = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
        __m256d w = _mm256_set_pd(4.0, 3.0, 2.0, 1.0);
        __m256d d = _mm256_add_pd(z, w);
        alignas(32) double result_array[4];
        _mm256_store_pd(result_array, d);
        std::cout << "结果: ";
        for(int i=0; i<4; ++i) {
            std::cout << result_array[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "\n[AVX] ⚠️  警告：CPU 不支持 AVX，跳过 AVX 示例" << std::endl;
        std::cout << "     如果强制执行会导致程序崩溃 (SIGILL 信号)" << std::endl;
    }
}

int main() {
    // 获取 CPU 信息和特性
    CPUFeatures features = get_cpu_info();
    
    // 根据 CPU 特性运行示例
    intrinsics_example(features);
    
    return 0;
}