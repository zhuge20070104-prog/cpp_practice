#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "common.h"

// 全局配置，确保 grid/block 策略一致
const int DATA_SIZE = 1 << 22;

__global__ void test_unified_memory(float* a, float* b, float* c, int size) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    if(gid < size) {
        c[gid] = a[gid] + b[gid];
    }
}


int main(int argc, char** argv) {
    unsigned int byte_size = DATA_SIZE * sizeof(float);
    printf("Input size: %d\n", DATA_SIZE);

    float* A, *B, *ref, *C;

    gpuErrCheck(cudaMallocManaged((void**)&A, byte_size));
    gpuErrCheck(cudaMallocManaged((void**)&B, byte_size));
    gpuErrCheck(cudaMallocManaged((void**)&ref, byte_size));

    C = (float*)malloc(byte_size);

    if(!A || !B || !ref || !C) {
        printf("host memory allocation error \n");
        if(A) free(A);
        if(B) free(B);
        if(ref) free(ref);
        if(C) free(C);
        return EXIT_FAILURE;
    }


    for(std::size_t i=0; i<DATA_SIZE; i++) {
        A[i] = i % 10;
        B[i] = i % 7;
    }

    sum_array_cpu(A, B, C, DATA_SIZE);

    int block_size = 128;
    dim3 block(block_size);
    dim3 grid((DATA_SIZE + block.x - 1) / block.x);

    printf("Kernel is launched with grid(%d,%d,%d) and block(%d,%d,%d) \n",
        grid.x, grid.y, grid.z, block.x, block.y, block.z);
        
    test_unified_memory<<<grid, block>>>(A, B, ref, DATA_SIZE);
    gpuErrCheck(cudaDeviceSynchronize());

    compare_results(ref, C, DATA_SIZE);
    free(C);
    return EXIT_SUCCESS;
}
