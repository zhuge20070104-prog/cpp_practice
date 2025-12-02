#ifndef _FREDRIC_COMMON_H_
#define _FREDRIC_COMMON_H_

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>


#define gpuErrCheck(ans) { gpuAssert((ans), __FILE__, __LINE__); }

inline void gpuAssert(cudaError_t code, const char* file, int line, bool abort=true) {
    if(code != cudaSuccess) {
        fprintf(stderr, "GPUAssert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if(abort) {
            exit(code);
        }
    }
}

inline void compare_results(int* a, int* b, int size) {
    for(int i=0; i<size; i++) {
        if(a[i] != b[i]) {
            printf("Arrays are different\n");
            return;
        }
    }

    printf("Arrays are the same\n");
}

enum INIT_PARAM{
	INIT_ZERO,INIT_RANDOM,INIT_ONE,INIT_ONE_TO_TEN,INIT_FOR_SPARSE_METRICS,INIT_0_TO_X
};

void sum_array_cpu(float* a, float* b, float* c, int size);

// Initialize the integer input array
void initialize(int * input, const int array_size,
	INIT_PARAM PARAM = INIT_ONE_TO_TEN, int x = 0);

//reduction in cpu
int reduction_cpu(int * input, const int size);

void compare_results(int gpu_result, int cpu_result);
void compare_results(float gpu_result, float cpu_result);
#endif