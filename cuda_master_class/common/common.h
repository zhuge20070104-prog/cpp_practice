#ifndef _FREDRIC_COMMON_H_
#define _FREDRIC_COMMON_H_

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>


#define gpuErrCheck(ans) { gpuAssert((ans), __FILE__, __LINE__); }

inline void gpuAssert(cudaError_t code, const char* file, int line, bool abort=true) {
    if(code != cudaSuccess) {
        fprintf(stderr, "GPUAssert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if(abort) {
            exit(code);
        }
    }
}

void compare_results(int* a, int* b, int size) {
    for(int i=0; i<size; i++) {
        if(a[i] != b[i]) {
            printf("Arrays are different\n");
            return;
        }
    }

    printf("Arrays are the same\n");
}


#endif