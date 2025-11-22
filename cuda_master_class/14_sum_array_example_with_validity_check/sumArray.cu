#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>


void sum_array_cpu(int* a, int* b, int* c, int size) {
    for(int i=0; i<size; i++) {
        c[i] = a[i] + b[i];
    }
}

__global__ void sum_array_gpu(int* a, int* b, int* c, int size) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    if(gid < size) {
        c[gid] = a[gid] + b[gid];
    }
}

TEST_CASE("Sum Array Example with Validity Check") {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Sum Array Example with Validity Check" << std::endl;

    int size = 10000;
    int block_size = 128;

    int NO_BYTES = size * sizeof(int);
    int* h_a = (int*)malloc(NO_BYTES);
    int* h_b = (int*)malloc(NO_BYTES);
    int* h_c = (int*)malloc(NO_BYTES);
    int* gpu_results = (int*)malloc(NO_BYTES);


    time_t t;
    srand((unsigned)time(&t));

    for(int i=0; i<size; i++) {
        h_a[i] = (int)(rand() & 0xff);
    }

    for(int i=0; i<size; i++) {
        h_b[i] = (int)(rand() & 0xff);
    }

    memset(gpu_results, 0, NO_BYTES);

    int* d_a, *d_b, *d_c;
    cudaMalloc((void**)&d_a, NO_BYTES);
    cudaMalloc((void**)&d_b, NO_BYTES);
    cudaMalloc((void**)&d_c, NO_BYTES);

    cudaMemcpy(d_a, h_a, NO_BYTES, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, NO_BYTES, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, gpu_results, NO_BYTES, cudaMemcpyHostToDevice);

    dim3 block(block_size);
    dim3 grid((size / block.x) + 1);
    sum_array_gpu<<<grid, block>>>(d_a, d_b, d_c, size);
    cudaDeviceSynchronize();
    cudaMemcpy(gpu_results, d_c, NO_BYTES, cudaMemcpyDeviceToHost);
    sum_array_cpu(h_a, h_b, h_c, size);

    compare_results(h_c, gpu_results, size);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(h_a);
    free(h_b);
    free(h_c);
    free(gpu_results);
    cudaDeviceReset();
}




