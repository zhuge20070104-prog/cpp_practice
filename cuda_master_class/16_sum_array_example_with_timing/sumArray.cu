#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>
#include <time.h>


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


void test_sum_array_with_timing(int block_size) {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Sum Array Example with timing - Blocksize: " << block_size << std::endl;

    int size = 10000;

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
    gpuErrCheck(cudaMalloc((void**)&d_a, NO_BYTES));
    gpuErrCheck(cudaMalloc((void**)&d_b, NO_BYTES));
    gpuErrCheck(cudaMalloc((void**)&d_c, NO_BYTES));

    clock_t htod_start, htod_end;
    htod_start = clock(); 
    gpuErrCheck(cudaMemcpy(d_a, h_a, NO_BYTES, cudaMemcpyHostToDevice));
    gpuErrCheck(cudaMemcpy(d_b, h_b, NO_BYTES, cudaMemcpyHostToDevice));
    htod_end = clock();


    dim3 block(block_size);
    dim3 grid((size / block.x) + 1);

    clock_t gpu_start, gpu_end;
    gpu_start = clock();
    sum_array_gpu<<<grid, block>>>(d_a, d_b, d_c, size);
    gpuErrCheck(cudaDeviceSynchronize());
    gpu_end = clock();

    clock_t dtoh_start, dtoh_end;
    dtoh_start = clock();
    gpuErrCheck(cudaMemcpy(gpu_results, d_c, NO_BYTES, cudaMemcpyDeviceToHost));
    dtoh_end = clock();

    // Summation in CPU
    clock_t cpu_start, cpu_end;
    cpu_start = clock();
    sum_array_cpu(h_a, h_b, h_c, size);
    cpu_end = clock();
    printf("Sum array cpu execution time: %4.6f\n", 
        (double)((double)(cpu_end - cpu_start)/CLOCKS_PER_SEC));

    printf("htod mem transfer time: %4.6f\n", 
        (double)((double)(htod_end - htod_start)/CLOCKS_PER_SEC));

    printf("gpu kernel execution time: %4.6f\n", 
        (double)((double)(gpu_end - gpu_start)/CLOCKS_PER_SEC));

    printf("dtoh mem transfer time: %4.6f\n", 
        (double)((double)(dtoh_end - dtoh_start)/CLOCKS_PER_SEC));

    printf("Sum array GPU total execution time: %4.6f\n", 
        (double)((double)(dtoh_end - htod_start)/CLOCKS_PER_SEC));

    compare_results(h_c, gpu_results, size);

    gpuErrCheck(cudaFree(d_a));
    gpuErrCheck(cudaFree(d_b));
    gpuErrCheck(cudaFree(d_c));
    free(h_a);
    free(h_b);
    free(h_c);
    free(gpu_results);
    gpuErrCheck(cudaDeviceReset());
}

TEST_CASE("Sum Array Example with timing - Blocksize 128") {
    test_sum_array_with_timing(128);
}

TEST_CASE("Sum Array Example with timing - Blocksize 256") {
    test_sum_array_with_timing(256);
}

TEST_CASE("Sum Array Example with timing - Blocksize 512") {
    test_sum_array_with_timing(512);
}

TEST_CASE("Sum Array Example with timing - Blocksize 1024") {
    test_sum_array_with_timing(1024);
}




