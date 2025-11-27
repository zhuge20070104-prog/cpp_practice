#define CATCH_CONFIG_MAIN
#include "cuda_runtime.h"
#include "catch2/catch.hpp"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// ============================================================
// 2. Warp Unrolling 优化版本
// ============================================================
__global__ void reduction_warp_unrolling(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    int gid = blockIdx.x * blockDim.x + threadIdx.x;

    if(gid > size) {
        return;
    }

    int* i_data = input + blockDim.x * blockIdx.x;

    // 步骤1：正常循环，直到 offset = 32（只剩1个Warp）
    for(int offset = blockDim.x / 2; offset >= 64; offset /= 2) {
        if (tid < offset) {
            i_data[tid] += i_data[tid + offset];
        }
        __syncthreads();
    }

    // 步骤2：手动展开最后1个Warp的归约（消除Warp Divergence）
    if (tid < 32) {
        // 使用 volatile 防止编译器优化
        // 确保每次写入都立即生效，其他线程能立即看到
        volatile int* vsmem = i_data;
        
        // offset = 32
        vsmem[tid] += vsmem[tid + 32];
        
        // offset = 16
        vsmem[tid] += vsmem[tid + 16];
        
        // offset = 8
        vsmem[tid] += vsmem[tid + 8];
        
        // offset = 4
        vsmem[tid] += vsmem[tid + 4];
        
        // offset = 2
        vsmem[tid] += vsmem[tid + 2];
        
        // offset = 1
        vsmem[tid] += vsmem[tid + 1];
        
        // 不需要 __syncthreads()！
        // 因为 Warp 内的32个线程是硬件同步的
    }

    if (tid == 0) {
        temp[blockIdx.x] = i_data[0];
    }
}



// ============================================================
// 测试函数
// ============================================================
using ReductionKernel = void (*)(int*, int*, int);


// 通用的 reduction 测试函数
void test_reduction(const char* kernel_name, ReductionKernel kernel_func, int size = 1 << 10) {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Testing: " << kernel_name << std::endl;

    int byte_size = size * sizeof(int);
    int block_size = 128;

    int* h_input, *h_ref;

    h_input = (int*)malloc(byte_size);
    initialize(h_input, size, INIT_RANDOM);
    
    // 打印前10个元素验证随机性
    printf("前10个元素: ");
    for(int i=0; i<10; i++) printf("%d ", h_input[i]);
    printf("\n");
    
    int cpu_result = reduction_cpu(h_input, size);

    dim3 block(block_size);
    dim3 grid(size/block.x);

    printf("Kernel launch parameters: %d blocks of %d threads\n", grid.x, block.x);

    int temp_array_byte_size = sizeof(int) * grid.x;
    h_ref = (int*)malloc(temp_array_byte_size);

    int* d_input, *d_temp;
    gpuErrCheck(cudaMalloc((void**)&d_input, byte_size));
    gpuErrCheck(cudaMalloc((void**)&d_temp, temp_array_byte_size));
    gpuErrCheck(cudaMemcpy(d_input, h_input, byte_size, cudaMemcpyHostToDevice));
    gpuErrCheck(cudaMemset(d_temp, 0, temp_array_byte_size));

    // 调用传入的 kernel 函数
    kernel_func<<<grid, block>>>(d_input, d_temp, size);
    gpuErrCheck(cudaDeviceSynchronize());

    gpuErrCheck(cudaMemcpy(h_ref, d_temp, temp_array_byte_size, cudaMemcpyDeviceToHost));

    int gpu_result = 0;
    for(int i=0; i<grid.x; i++) {
        gpu_result += h_ref[i];
    }

    compare_results(gpu_result, cpu_result);

    gpuErrCheck(cudaFree(d_input));
    gpuErrCheck(cudaFree(d_temp));
    free(h_input);
    free(h_ref);
}


TEST_CASE("Parallel Reduction as Warp Unrolling") {
    test_reduction("reduction_warp_unrolling", reduction_warp_unrolling);
    gpuErrCheck(cudaDeviceReset());
}
