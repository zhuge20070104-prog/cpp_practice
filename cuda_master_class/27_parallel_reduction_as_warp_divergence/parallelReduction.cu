#define CATCH_CONFIG_MAIN
#include "cuda_runtime.h"
#include "catch2/catch.hpp"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


__global__ void reduce_neighbored_pair_redindex(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    int gid = blockDim.x * blockIdx.x + threadIdx.x;

    if(gid > size) {
        return;
    }

    // 局部数据块指针：指向当前 block 的数据起始位置
    int* i_data = input + blockDim.x * blockIdx.x;

    for(int offset=1; offset<=blockDim.x/2; offset*=2) {
        // 关键改进：让连续的线程工作，避免 warp divergence
        int index = 2 * offset * tid;
        
        if(index < blockDim.x) {
            i_data[index] += i_data[index + offset];
        }
        __syncthreads();
    }

    if(tid == 0) {
        temp[blockIdx.x] = i_data[0];  // 使用 i_data[0] 而不是 input[gid]
    }
}


// 定义 kernel 函数指针类型
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


TEST_CASE("Parallel Reduction without Warp Divergence - Reindex") {
    test_reduction("reduce_neighbored_pair_redindex", reduce_neighbored_pair_redindex);
    gpuErrCheck(cudaDeviceReset());
}


__global__ void reduction_with_interleave_pair(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    int gid = blockIdx.x * blockDim.x + threadIdx.x;

    if(gid > size) {
        return;
    }

    for(int offset = blockDim.x/2; offset > 0; offset /= 2) {
        if(tid < offset) {
            input[gid] += input[gid + offset];
        }
        __syncthreads();
    }

    if(tid == 0) {
        temp[blockIdx.x] = input[gid];
    }
}

TEST_CASE("Parallel Reduction without Warp Divergence - Interleave Pairs") {
    test_reduction("reduction_with_interleave_pair", reduction_with_interleave_pair);
    gpuErrCheck(cudaDeviceReset());
}