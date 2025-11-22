#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>


__global__ void mem_trs_test1(int* input) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    printf("tid: %d, gid: %d, value: %d\n",
        threadIdx.x, gid, input[gid]);
}

TEST_CASE("Memory Transfer Between Host and Device - 1") {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Memory Transfer Between Host and Device - 1" << std::endl;

    int size = 128;

    int byte_size = size * sizeof(int);
    int* h_input = (int*)malloc(byte_size);

    time_t t;
    srand((unsigned)time(&t));
    for(int i=0; i<size; i++) {
        h_input[i] = (int)(rand() & 0xff);
    }



    int* d_input;
    cudaMalloc((void**)&d_input, byte_size);
    cudaMemcpy(d_input, h_input, byte_size, cudaMemcpyHostToDevice);
    dim3 block(64);
    dim3 grid(2);

    mem_trs_test1<<<grid, block>>>(d_input);
    cudaDeviceSynchronize();
    cudaFree(d_input);
    free(h_input);
    cudaDeviceReset();
}

__global__ void mem_trs_test2(int* input, int size) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    if(gid < size) {
        printf("tid: %d, gid: %d, value: %d\n",
            threadIdx.x, gid, input[gid]);
    }
}

TEST_CASE("Memory Transfer Between Host and Device - 2") {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Memory Transfer Between Host and Device - 2" << std::endl;
    int size = 159;

    int byte_size = size * sizeof(int);
    int* h_input = (int*)malloc(byte_size);

    time_t t;
    srand((unsigned)time(&t));
    for(int i=0; i<size; i++) {
        h_input[i] = (int)(rand() & 0xff);
    }

    int* d_input;
    cudaMalloc((void**)&d_input, byte_size);
    cudaMemcpy(d_input, h_input, byte_size, cudaMemcpyHostToDevice);
    dim3 block(32);
    dim3 grid(5);

    mem_trs_test2<<<grid, block>>>(d_input, size);
    cudaDeviceSynchronize();
    cudaFree(d_input);
    free(h_input);
    cudaDeviceReset();
}
