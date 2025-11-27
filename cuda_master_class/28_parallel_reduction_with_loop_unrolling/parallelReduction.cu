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


// ============================================================
// 2. Unrolling 2 个 block的代码
// ============================================================
__global__ void reduction_unrolling_blocks2(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    // 计算数据的偏移量
    int BLOCK_OFFSET = blockIdx.x * blockDim.x * 2;
    int index = BLOCK_OFFSET + tid;

    // 指向每个block负责的数据块起始位置
    int* i_data = input + BLOCK_OFFSET;

    if((index + blockDim.x) < size) {
        input[index] += input[index + blockDim.x];
    }

    __syncthreads();

    // 步骤2：block内归约（复用上一节的算法）
    for(int offset = blockDim.x / 2; offset > 0; offset = offset / 2) {
        if (tid < offset) {
            i_data[tid] += i_data[tid + offset];
        }
        __syncthreads();
    }

    if(tid == 0) {
        temp[blockIdx.x] = i_data[0];
    }
}


// ============================================================
// 3. Unrolling 4 个 block的代码（图片中的实现）
// ============================================================
__global__ void reduction_unrolling_blocks4(int* input, int* temp, int size) {
    int tid = threadIdx.x;
    
    // 关键计算：每个block负责处理 4*blockDim.x 个数据
    int BLOCK_OFFSET = blockIdx.x * blockDim.x * 4;
    
    int index = BLOCK_OFFSET + tid;
    
    // 指向当前block负责的数据块起始位置
    int* i_data = input + BLOCK_OFFSET;
    
    // 步骤1：预归约 - 把4个数据块加起来
    // 让每个线程把4个对应位置的数据相加
    if ((index + 3 * blockDim.x) < size) {
        int a1 = input[index];                      // 第1个数据块
        int a2 = input[index + blockDim.x];         // 第2个数据块
        int a3 = input[index + 2 * blockDim.x];     // 第3个数据块
        int a4 = input[index + 3 * blockDim.x];     // 第4个数据块
        input[index] = a1 + a2 + a3 + a4;           // 结果保存到第1个位置
    }
    __syncthreads();
    
    // 步骤2：block内归约（复用上一节的interleave算法）
    for(int offset = blockDim.x / 2; offset > 0; offset = offset / 2) {
        if (tid < offset) {
            i_data[tid] += i_data[tid + offset];
        }
        __syncthreads();
    }
    
    // 步骤3：保存结果
    if (tid == 0) {
        temp[blockIdx.x] = i_data[0];
    }
}


// 定义 kernel 函数指针类型
using ReductionKernel = void (*)(int*, int*, int);

// ============================================================
// 通用的 reduction 测试函数（不使用unrolling）
// ============================================================
void test_reduction(const char* kernel_name, ReductionKernel kernel_func, int size = 1 << 10) {
    std::cout << "\n================================" << std::endl;
    std::cout << "Testing: " << kernel_name << std::endl;
    std::cout << "策略：不使用 unrolling" << std::endl;

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
    dim3 grid(size/block.x);  // 不使用unrolling：grid = size / block_size

    printf("📊 Kernel launch参数:\n");
    printf("   - 数据总数: %d\n", size);
    printf("   - Block size: %d\n", block.x);
    printf("   - Grid size: %d blocks\n", grid.x);
    printf("   - 每个block处理: %d 个数据\n", block.x);

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

    printf("✅ CPU结果: %d\n", cpu_result);
    printf("✅ GPU结果: %d\n", gpu_result);
    compare_results(gpu_result, cpu_result);

    gpuErrCheck(cudaFree(d_input));
    gpuErrCheck(cudaFree(d_temp));
    free(h_input);
    free(h_ref);
}


// ============================================================
// 使用 unrolling 的测试函数
// unroll_factor: 2, 4, 8 表示unrolling 2/4/8个block
// ============================================================
void test_reduction_unrolling(const char* kernel_name, ReductionKernel kernel_func, 
                               int unroll_factor, int size = 1 << 10) {
    std::cout << "\n================================" << std::endl;
    std::cout << "Testing: " << kernel_name << std::endl;
    std::cout << "策略：Unrolling " << unroll_factor << " 个 blocks" << std::endl;

    int byte_size = size * sizeof(int);
    int block_size = 128;

    int* h_input, *h_ref;

    h_input = (int*)malloc(byte_size);
    initialize(h_input, size, INIT_RANDOM);
    
    printf("前10个元素: ");
    for(int i=0; i<10; i++) printf("%d ", h_input[i]);
    printf("\n");
    
    int cpu_result = reduction_cpu(h_input, size);

    dim3 block(block_size);
    // 关键修改：grid size 要除以 unroll_factor
    dim3 grid((size / block.x) / unroll_factor);

    printf("📊 Kernel launch参数:\n");
    printf("   - 数据总数: %d\n", size);
    printf("   - Block size: %d\n", block.x);
    printf("   - Unroll factor: %d\n", unroll_factor);
    printf("   - Grid size: %d blocks (原来是 %d，除以unroll_factor后)\n", 
           grid.x, size/block.x);
    printf("   - 每个block处理: %d × %d = %d 个数据\n", 
           block.x, unroll_factor, block.x * unroll_factor);

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

    printf("✅ CPU结果: %d\n", cpu_result);
    printf("✅ GPU结果: %d\n", gpu_result);
    compare_results(gpu_result, cpu_result);

    gpuErrCheck(cudaFree(d_input));
    gpuErrCheck(cudaFree(d_temp));
    free(h_input);
    free(h_ref);
}


// ============================================================
// 测试用例
// ============================================================

TEST_CASE("1. Basic method - no unrolling") {
    test_reduction("reduce_neighbored_pair_redindex (basic)", 
                   reduce_neighbored_pair_redindex);
    gpuErrCheck(cudaDeviceReset());
}

TEST_CASE("2. Unrolling 2 blocks") {
    test_reduction_unrolling("reduction_unrolling_blocks2", 
                             reduction_unrolling_blocks2, 
                             2);  // unroll_factor = 2
    gpuErrCheck(cudaDeviceReset());
}

TEST_CASE("3. Unrolling 4 blocks") {
    test_reduction_unrolling("reduction_unrolling_blocks4", 
                             reduction_unrolling_blocks4, 
                             4);  // unroll_factor = 4
    gpuErrCheck(cudaDeviceReset());
}