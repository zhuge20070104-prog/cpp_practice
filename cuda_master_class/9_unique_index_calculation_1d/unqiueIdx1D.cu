#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>


__global__ void unique_idx_calc_threadIdx(int* input) {
    int tid = threadIdx.x;
    printf("threadIdx: %d, value: %d\n", tid, input[tid]);
}

TEST_CASE("Unique Index Calculation 1D - Single block") {
    int array_size = 8;
    int array_byte_size = array_size * sizeof(int);
    int h_data[] = {23, 9, 4, 53, 65, 12, 1, 33};
    for(int i=0; i<array_size; i++) {
        printf("%d ", h_data[i]);
    }

    printf("\n\n");

    int* d_data;
    cudaMalloc((void**)&d_data, array_byte_size);
    cudaMemcpy(d_data, h_data, array_byte_size, cudaMemcpyHostToDevice);
    dim3 block(8);
    dim3 grid(1);

    unique_idx_calc_threadIdx<<<grid, block>>>(d_data);
    cudaDeviceSynchronize();
    cudaFree(d_data);
    cudaDeviceReset();
}

__global__ void unique_gid_calculation(int* input) {
    int tid = threadIdx.x;
    int offset = blockIdx.x * blockDim.x;
    int gid = tid + offset;
    printf("blockIdx.x: %d, threadIdx.x: %d, gid: %d, value: %d\n", 
        blockIdx.x, threadIdx.x, gid, input[gid]);
}

TEST_CASE("Unique Index Calculation 1D - Multiple blocks") {
    int array_size = 16;
    int array_byte_size = array_size * sizeof(int);
    int h_data[] = {23, 9, 4, 53, 65, 12, 1, 33, 87, 45, 43, 52, 69, 32, 11, 47};
    for(int i=0; i<array_size; i++) {
        printf("%d ", h_data[i]);
    }

    printf("\n\n");
    int* d_data;
    cudaMalloc((void**)&d_data, array_byte_size);
    cudaMemcpy(d_data, h_data, array_byte_size, cudaMemcpyHostToDevice);
    
    dim3 block(4);
    dim3 grid(4);

    unique_gid_calculation<<<grid, block>>>(d_data);
    cudaDeviceSynchronize();

    cudaFree(d_data);
    cudaDeviceReset();
    REQUIRE(true);
}
