#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <memory>
#include "utilities.h"

__global__ void add(int a, int b, int *c) {
    *c = a + b;
}

int main(int argc, char* argv[]) {
    int c;
    int *dev_c;
    HANDLE_ERROR(cudaMalloc((void**)&dev_c, sizeof(int)));
    add<<<1, 1>>>(3, 8, dev_c);
    HANDLE_ERROR(cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost));
    std::cout << "3 + 8 = " << c << "\n";
    HANDLE_ERROR(cudaFree(dev_c));
    return EXIT_SUCCESS;
}