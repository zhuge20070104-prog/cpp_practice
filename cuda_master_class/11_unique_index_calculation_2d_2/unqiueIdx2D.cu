#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>


__global__ void unique_gid_calculation(int* input) {
    int tid = blockDim.x * threadIdx.y + threadIdx.x;
    int offset = blockDim.x * blockDim.y * blockIdx.x;
    int row_offset = blockDim.x * blockDim.y * gridDim.x * blockIdx.y;
    int gid = tid + offset + row_offset;
    printf("blockIdx.x: %d, blockIdx.y: %d, gid: %d, value: %d\n", 
        blockIdx.x, blockIdx.y, gid, input[gid]);
}

TEST_CASE("Unique Index Calculation 2D - Multiple blocks") {
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
    
    dim3 block(2, 2);
    dim3 grid(2, 2);

    unique_gid_calculation<<<grid, block>>>(d_data);
    cudaDeviceSynchronize();

    cudaFree(d_data);
    cudaDeviceReset();
    REQUIRE(true);
}
