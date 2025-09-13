#ifndef _FREDRIC_UTILITIES_H_
#define _FREDRIC_UTILITIES_H_

#include "cuda.h"
#include <stdio.h>

static void HandleError(cudaError_t err, 
                char const* file, 
                int line) {
    if(err != cudaSuccess) {
        printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
        exit(EXIT_FAILURE);
    }
}

#define HANDLE_ERROR(err) (HandleError(err, __FILE__, __LINE__))

#endif