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


__global__ void test_sum_array_for_memory(float* a, float* b, float* c, int size) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;

    if(gid < size) {
        c[gid] = a[gid] + b[gid];
    }
}


int main(int argc, char** argv) {
    printf("Running 1D grid\n");

    int size = 1 << 22;

    int block_size = 128;
    if(argc > 1) {
        block_size = 1 << atoi(argv[1]);
    }

    printf("Entered block size: %d \n", block_size);
    unsigned int byte_size = size * sizeof(float);

    // host memory allocation
    float* h_a, * h_b, * h_c, * h_ref;
    h_a   = (float*)malloc(byte_size);
    h_b   = (float*)malloc(byte_size);
    h_c   = (float*)malloc(byte_size);
    h_ref = (float*)malloc(byte_size);

    if(!h_a || !h_b || !h_c || !h_ref) {
        printf("host memory allocation error \n");
        if(h_a)   free(h_a);
        if(h_b)   free(h_b);
        if(h_c)   free(h_c);
        if(h_ref) free(h_ref);
        return -1;
    }

    // initialize host data
    for(int i = 0; i < size; i++) {
        h_a[i] = i % 10;
        h_b[i] = i % 7;
    }

    // CPU reference result
    for(int i = 0; i < size; i++) {
        h_ref[i] = h_a[i] + h_b[i];
    }

    dim3 block(block_size);
    dim3 grid((size + block.x - 1) / block.x);

    printf("Kernel is launch with grid(%d,%d,%d) and block(%d,%d,%d) \n",
        grid.x, grid.y, grid.z, block.x, block.y, block.z);

    // device memory allocation
    float* d_a, * d_b, * d_c;
    gpuErrCheck(cudaMalloc((void**)&d_a, byte_size));
    gpuErrCheck(cudaMalloc((void**)&d_b, byte_size));
    gpuErrCheck(cudaMalloc((void**)&d_c, byte_size));

    gpuErrCheck(cudaMemset(d_c, 0, byte_size));

    // host to device copy
    gpuErrCheck(cudaMemcpy(d_a, h_a, byte_size, cudaMemcpyHostToDevice));
    gpuErrCheck(cudaMemcpy(d_b, h_b, byte_size, cudaMemcpyHostToDevice));

    // kernel launch
    test_sum_array_for_memory<<<grid, block>>>(d_a, d_b, d_c, size);
    gpuErrCheck(cudaDeviceSynchronize());

    // device to host copy
    gpuErrCheck(cudaMemcpy(h_c, d_c, byte_size, cudaMemcpyDeviceToHost));

    // verify results
    bool match = true;
    for(int i = 0; i < size; i++) {
        if(h_c[i] != h_ref[i]) {
            match = false;
            printf("Result mismatch at index %d: host %f, device %f\n",
                i, h_ref[i], h_c[i]);
            break;
        }
    }

    if(match) {
        printf("Results match! \n");
    }

    // cleanup
    gpuErrCheck(cudaFree(d_a));
    gpuErrCheck(cudaFree(d_b));
    gpuErrCheck(cudaFree(d_c));

    free(h_a);
    free(h_b);
    free(h_c);
    free(h_ref);

    gpuErrCheck(cudaDeviceReset());

    return 0;
}
