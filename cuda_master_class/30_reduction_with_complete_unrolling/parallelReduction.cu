#define CATCH_CONFIG_MAIN
#include "cuda_runtime.h"
#include "catch2/catch.hpp"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// ============================================================
// 2. Complete Unrolling（完全展开）
// ============================================================
__global__ void reduction_complete_unrolling(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    int* i_data = input + blockDim.x * blockIdx.x;

    // 关键：根据 blockDim.x 的值，手动展开所有迭代！
    // 不再有循环！全部是直接的 if 语句！
    
    // blockDim.x == 1024: 需要 9 轮（512, 256, 128, 64, 32, 16, 8, 4, 2, 1）
    if (blockDim.x == 1024 && tid < 512)
        i_data[tid] += i_data[tid + 512];
    __syncthreads();
    
    // blockDim.x >= 512: 需要这一轮
    if (blockDim.x >= 512 && tid < 256)
        i_data[tid] += i_data[tid + 256];
    __syncthreads();
    
    // blockDim.x >= 256: 需要这一轮
    if (blockDim.x >= 256 && tid < 128)
        i_data[tid] += i_data[tid + 128];
    __syncthreads();
    
    // blockDim.x >= 128: 需要这一轮
    if (blockDim.x >= 128 && tid < 64)
        i_data[tid] += i_data[tid + 64];
    __syncthreads();
    
    // 最后32个线程（Warp Unrolling）
    if (tid < 32) {
        volatile int* vsmem = i_data;
        
        // blockDim.x >= 64: 需要这一轮
        if (blockDim.x >= 64)
            vsmem[tid] += vsmem[tid + 32];
        
        // blockDim.x >= 32: 需要这一轮
        if (blockDim.x >= 32)
            vsmem[tid] += vsmem[tid + 16];
        
        // blockDim.x >= 16: 需要这一轮
        if (blockDim.x >= 16)
            vsmem[tid] += vsmem[tid + 8];
        
        // blockDim.x >= 8: 需要这一轮
        if (blockDim.x >= 8)
            vsmem[tid] += vsmem[tid + 4];
        
        // blockDim.x >= 4: 需要这一轮
        if (blockDim.x >= 4)
            vsmem[tid] += vsmem[tid + 2];
        
        // blockDim.x >= 2: 需要这一轮
        if (blockDim.x >= 2)
            vsmem[tid] += vsmem[tid + 1];
    }

    if (tid == 0) {
        temp[blockIdx.x] = i_data[0];
    }
}


// ============================================================
// 测试函数
// ============================================================
using ReductionKernel = void (*)(int*, int*, int);

void test_reduction(const char* kernel_name, ReductionKernel kernel_func, 
                    int block_size = 128, int size = 1 << 15) {
    std::cout << "\n================================" << std::endl;
    std::cout << "Testing: " << kernel_name << std::endl;
    std::cout << "Block size: " << block_size << std::endl;

    int byte_size = size * sizeof(int);

    int* h_input, *h_ref;

    h_input = (int*)malloc(byte_size);
    initialize(h_input, size, INIT_RANDOM);
    
    printf("Data size: %d\n", size);
    printf("First 10 elements: ");
    for(int i=0; i<10; i++) printf("%d ", h_input[i]);
    printf("\n");
    
    int cpu_result = reduction_cpu(h_input, size);

    dim3 block(block_size);
    dim3 grid(size/block.x);

    printf("Kernel launch: %d blocks × %d threads = %d threads total\n", 
           grid.x, block.x, grid.x * block.x);

    int temp_array_byte_size = sizeof(int) * grid.x;
    h_ref = (int*)malloc(temp_array_byte_size);

    int* d_input, *d_temp;
    gpuErrCheck(cudaMalloc((void**)&d_input, byte_size));
    gpuErrCheck(cudaMalloc((void**)&d_temp, temp_array_byte_size));
    gpuErrCheck(cudaMemcpy(d_input, h_input, byte_size, cudaMemcpyHostToDevice));
    gpuErrCheck(cudaMemset(d_temp, 0, temp_array_byte_size));

    kernel_func<<<grid, block>>>(d_input, d_temp, size);
    gpuErrCheck(cudaDeviceSynchronize());

    gpuErrCheck(cudaMemcpy(h_ref, d_temp, temp_array_byte_size, cudaMemcpyDeviceToHost));

    int gpu_result = 0;
    for(int i=0; i<grid.x; i++) {
        gpu_result += h_ref[i];
    }

    printf("CPU result: %d\n", cpu_result);
    printf("GPU result: %d\n", gpu_result);
    compare_results(gpu_result, cpu_result);

    gpuErrCheck(cudaFree(d_input));
    gpuErrCheck(cudaFree(d_temp));
    free(h_input);
    free(h_ref);
}


TEST_CASE("2. Complete Unrolling (no loop!) - 128 threads") {
    test_reduction("reduction_complete_unrolling", reduction_complete_unrolling, 128);
    gpuErrCheck(cudaDeviceReset());
}

TEST_CASE("3. Complete Unrolling (no loop!) - 256 threads") {
    test_reduction("reduction_complete_unrolling", reduction_complete_unrolling, 256);
    gpuErrCheck(cudaDeviceReset());
}

TEST_CASE("4. Complete Unrolling (no loop!) - 512 threads") {
    test_reduction("reduction_complete_unrolling", reduction_complete_unrolling, 512);
    gpuErrCheck(cudaDeviceReset());
}

TEST_CASE("5. Complete Unrolling (no loop!) - 1024 threads") {
    test_reduction("reduction_complete_unrolling", reduction_complete_unrolling, 1024);
    gpuErrCheck(cudaDeviceReset());
}
