#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>
#include <time.h>


__global__ void occupancy_test(int* results) {
	int gid = blockIdx.x * blockDim.x + threadIdx.x;
	int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 4;
    int x5 = 5;
    int x6 = 6;
    int x7 = 7;
    int x8 = 8;
    results[gid] = x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;
}


TEST_CASE("Occupancy Test") {
	printf("--------------------------------\n");
	printf("Occupancy Test\n");

	int size = 1 << 16;
    int byte_size = size * sizeof(int);
    int* d_results;
    gpuErrCheck(cudaMalloc((void**)&d_results, byte_size));
    gpuErrCheck(cudaMemset(d_results, 0, byte_size));

    dim3 blocks(128);
    dim3 grid((size + blocks.x - 1)/blocks.x);
    occupancy_test<<<grid, blocks>>>(d_results);

	gpuErrCheck(cudaDeviceSynchronize());
	gpuErrCheck(cudaDeviceReset());
}