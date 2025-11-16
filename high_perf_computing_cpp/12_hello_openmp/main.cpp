#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <bitset>
#include <cpuid.h>
#include <cstring>
#include <chrono>
#include <random>
#include <omp.h>

void hello_openmp() {
    omp_set_num_threads(8);

#pragma omp parallel
{
    #pragma omp critical
    {
        std::cout << "Hello, OpenMP! " << omp_get_thread_num()
            << "/" << omp_get_num_threads() << std::endl;
    }
}

}

int main() {
    hello_openmp();
    return 0;
}