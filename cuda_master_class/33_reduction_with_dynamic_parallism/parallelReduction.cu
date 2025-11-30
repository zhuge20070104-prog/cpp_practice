// 33. Reduction with Dynamic Parallelism
// 这里完全按照你贴出的原始示例来实现：
//  - 多个 block 并行，每个 block 做一段数据的归约；
//  - 在 block 内部用递归的 child kernel 做 reduction；
//  - 部分和写到 g_odata[blockIdx.x]，最后在 CPU 端再做一次归约。

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "common.h"

// 和 31 章里一致的 host 端计时辅助函数
void print_time_using_host_clock(clock_t start, clock_t end) {
    printf("GPU execution time (host clock): %4.6f seconds\n",
        (double)((double)(end - start) / CLOCKS_PER_SEC));
}

// ---------------------------------------------------------------------------
// 递归 kernel：在一个 block 内对一段数据做归约
//  - g_idata：完整输入或某一段的起始地址
//  - g_odata：每个 block 的部分和数组
//  - isize  ：当前这一层参与归约的元素个数（初始为 blockDim.x）
// ---------------------------------------------------------------------------
// 递归 kernel：直接操作传入的数据指针，不做额外偏移
__global__ void gpuRecursiveReduceChild(int* idata, int* odata, unsigned int isize) {
    int tid = threadIdx.x;

    // stop condition：只剩两个元素时，由 tid==0 写回结果
    if (isize == 2 && tid == 0) {
        *odata = idata[0] + idata[1];
        return;
    }

    // nested invocation
    int istride = isize >> 1;
    if (tid < (int)istride) {
        // in-place reduction
        idata[tid] += idata[tid + istride];
    }

    // sync at block level
    __syncthreads();

    // nested invocation to generate child grids
    if (tid == 0) {
        gpuRecursiveReduceChild<<<1, istride>>>(idata, odata, istride);
    }

    // sync at block level again
    __syncthreads();
}

// 主 kernel：为每个 block 设置正确的数据指针
__global__ void gpuRecursiveReduce(int* g_idata, int* g_odata, unsigned int isize) {
    int tid = threadIdx.x;

    // 为当前 block 取出这段数据的起始地址和输出位置
    int* idata = g_idata + blockIdx.x * blockDim.x;
    int* odata = &g_odata[blockIdx.x];

    // 直接调用递归 child kernel
    if (tid == 0) {
        gpuRecursiveReduceChild<<<1, isize>>>(idata, odata, isize);
    }

    __syncthreads();
}

int main(int argc, char** argv) {
    printf("Running parallel reduction with dynamic parallelism (recursive) \n");

    // 先用小数据测试，找出问题
    int size = 1 << 20;
    int byte_size = size * sizeof(int);
    int block_size = 1024;        // 进一步减少 block 数量，提高成功率

    clock_t gpu_start, gpu_end, cpu_start, cpu_end;

    int* h_input = (int*)malloc(byte_size);
    int* h_ref = nullptr;

    // 用简单数据测试：全部填 1，结果应该是 size
    initialize(h_input, size, INIT_RANDOM);

    // CPU 端 reduction 作为参考
    cpu_start = clock();
    int cpu_result = reduction_cpu(h_input, size);
    cpu_end = clock();

    dim3 block(block_size);
    dim3 grid(size / block.x);

    printf("Kernel launch parameters || grid : %d, block : %d \n", grid.x, block.x);

    int temp_array_byte_size = sizeof(int) * grid.x;
    h_ref = (int*)malloc(temp_array_byte_size);

    int* d_input = nullptr;
    int* d_temp = nullptr;
    gpuErrCheck(cudaMalloc((void**)&d_input, byte_size));
    gpuErrCheck(cudaMalloc((void**)&d_temp, temp_array_byte_size));

    gpu_start = clock();

    gpuErrCheck(cudaMemset(d_temp, 0, temp_array_byte_size));
    gpuErrCheck(cudaMemcpy(d_input, h_input, byte_size, cudaMemcpyHostToDevice));

    // 每个 block 对自己负责的元素做递归动态并行归约
    gpuRecursiveReduce<<<grid, block>>>(d_input, d_temp, block_size);
    
    // 检查 CUDA 错误
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("CUDA kernel launch error: %s\n", cudaGetErrorString(err));
    }

    gpuErrCheck(cudaDeviceSynchronize());
    gpuErrCheck(cudaMemcpy(h_ref, d_temp, temp_array_byte_size, cudaMemcpyDeviceToHost));

    int gpu_result = 0;
    int non_zero_blocks = 0;
    for (int i = 0; i < grid.x; i++) {
        if (h_ref[i] != 0) {
            non_zero_blocks++;
        }
        gpu_result += h_ref[i];
    }
    
    printf("Non-zero blocks: %d / %d\n", non_zero_blocks, grid.x);
    if (non_zero_blocks > 0) {
        printf("Average per non-zero block: %d\n", gpu_result / non_zero_blocks);
    }

    gpu_end = clock();
    print_time_using_host_clock(gpu_start, gpu_end);

    printf("CPU kernel execution time : %4.6f \n",
        (double)((double)(cpu_end - cpu_start) / CLOCKS_PER_SEC));

    compare_results(gpu_result, cpu_result);

    gpuErrCheck(cudaFree(d_input));
    gpuErrCheck(cudaFree(d_temp));
    free(h_input);
    free(h_ref);

    gpuErrCheck(cudaDeviceReset());
    return 0;
}
