#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "common.h"

// 全局配置，确保 grid/block 策略一致
const int DATA_SIZE = 1 << 22;

// 1. 空 Kernel
__global__ void register_usage_test_empty() {
}


__global__ void register_usage_test_without_memory_writing() {
    int x1 = 3465;
    int x2 = 1768;
    int x3 = 453;
    int x4 = x1 + x2 + x3;
}

__global__ void register_usage_test_with_memory_writing(int* results, int size) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    int x1 = 3465;
    int x2 = 1768;
    int x3 = 453;
    int x4 = x1 + x2 + x3;
    if(gid < size) {
        results[gid] = x4;
    }
}

/**
 * @brief 最简化的 Kernel 测试器
 * 
 * 自动配置 Grid/Block，直接转发参数。
 */
template <typename KernelFunc, typename... Args>
void run_kernel_test(KernelFunc kernel, const char* name, Args... args) {
    dim3 block(128);
    dim3 grid((DATA_SIZE + block.x - 1) / block.x);

    printf("[RUN] %s\n", name);
    kernel<<<grid, block>>>(args...);
    
    gpuErrCheck(cudaGetLastError());
    gpuErrCheck(cudaDeviceSynchronize());
    printf("[DONE] %s\n", name);
}

TEST_CASE("Empty Kernel", "[empty]") {
    run_kernel_test(register_usage_test_empty, "register_usage_test_empty");
    gpuErrCheck(cudaDeviceReset());
}

TEST_CASE("Register Usage Test Without Memory Writing", "[register_usage_test_without_memory_writing]") {
    run_kernel_test(register_usage_test_without_memory_writing, "register_usage_test_without_memory_writing");
    gpuErrCheck(cudaDeviceReset());
}


TEST_CASE("Register Usage Test With Memory Writing", "[register_usage_test_with_memory_writing]") {
    int* d_results;
    gpuErrCheck(cudaMalloc((void**)&d_results, DATA_SIZE * sizeof(int)));
    gpuErrCheck(cudaMemset(d_results, 0, DATA_SIZE * sizeof(int)));
    run_kernel_test(register_usage_test_with_memory_writing, "register_usage_test_with_memory_writing", d_results, DATA_SIZE);
    gpuErrCheck(cudaFree(d_results));
    gpuErrCheck(cudaDeviceReset());
}