#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>
#include <time.h>


__global__ void print_details_of_warps() {
	int gid = blockIdx.y * blockDim.x * gridDim.x
	        + blockIdx.x * blockDim.x 
			+ threadIdx.x;
	
	int warp_id = threadIdx.x / 32;
	int gbid = gridDim.x * blockIdx.y + blockIdx.x;

	printf("tid: %d, bid.x: %d, bid.y: %d, gid: %d, warp_id: %d, gbid: %d\n",
		threadIdx.x, blockIdx.x, blockIdx.y, gid, warp_id, gbid);
}

TEST_CASE("Device Properties") {
	dim3 block_size(42);
	dim3 grid_size(2, 2);

	print_details_of_warps<<<grid_size, block_size>>>();
	gpuErrCheck(cudaDeviceSynchronize());
	gpuErrCheck(cudaDeviceReset());
}




