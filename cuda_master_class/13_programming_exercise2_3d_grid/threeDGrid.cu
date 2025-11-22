#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void mem_trs_test_3d_grid(int* input, int size) {
    int tid = blockDim.x * blockDim.y * threadIdx.z + blockDim.x * threadIdx.y 
        + threadIdx.x;
    int block_offset = gridDim.x * blockDim.x * gridDim.y * blockDim.y * blockDim.z * blockIdx.z +
        gridDim.x * blockDim.x * blockDim.y * blockIdx.y * blockDim.z +
        blockDim.x * blockDim.y * blockDim.z * blockIdx.x;
    int gid = tid + block_offset;
    if(gid < size) {
        printf("blockIdx.x: %d, blockIdx.y: %d, blockIdx.z: %d, tid: %d, gid: %d, value: %d\n",
            blockIdx.x, blockIdx.y, blockIdx.z, tid, gid, input[gid]);
    }
}


TEST_CASE("Memory Transfer Between Host and Device - 3D Grid") {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Memory Transfer Between Host and Device - 3D Grid" << std::endl;

    int size = 64;

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
    dim3 block(2, 2, 2);
    dim3 grid(2, 2, 2);

    mem_trs_test_3d_grid<<<grid, block>>>(d_input, size);
    cudaDeviceSynchronize();
    cudaFree(d_input);
    free(h_input);
    cudaDeviceReset();
}




