#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <memory>
#include "utilities.h"

__global__ void kernel(void) {}

int main(int argc, char* argv[]) {
    kernel<<<1, 1>>>();
    std::cout << "Hello world!\n";
    return EXIT_SUCCESS;
}