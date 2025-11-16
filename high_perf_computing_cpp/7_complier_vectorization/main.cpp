#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <bitset>
#include <cpuid.h>
#include <cstring>
#include <chrono>
#include <random>
#include <xmmintrin.h>  // SSE
#include <immintrin.h>  // AVX


void simple_mad(float* a, float* b, float* c, float* result, const int length) {
    for(int i=0; i<length; ++i) {
        result[i] = a[i] * b[i] + c[i];
    }
}

void optimization() {
    const int length = 1024 * 1024 * 64;
    float* a = new float[length];
    float* b = new float[length];
    float* c = new float[length];
    float* result = new float[length];

    std::mt19937_64 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for(int i=0; i<length; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
        c[i] = dist(rng);
    }

    auto begin = std::chrono::high_resolution_clock::now();
    simple_mad(a, b, c, result, length);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "MAD took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] result;    
}


int main() {
    optimization();
    return 0;
}