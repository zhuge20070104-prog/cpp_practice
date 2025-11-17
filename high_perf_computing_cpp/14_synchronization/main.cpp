#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <bitset>
#include <cpuid.h>
#include <cstring>
#include <chrono>
#include <random>
#include <thread>  // for std::this_thread::sleep_for
#include <omp.h>

TEST_CASE("Atomic operation") {
   printf("\nATOMIC\n");

   int sum = 0;
#pragma omp parallel for num_threads(128)
    for(int i = 0; i < 100; ++i) {
        #pragma omp atomic
        ++sum;
    }

    std::cout << "sum: " << sum << std::endl;
}


TEST_CASE("Ordered operation") {
    printf("\nORDERED\n");

    std::vector<int> squares;

#pragma omp parallel for ordered 
    for(int i=0; i<20; ++i) {
        printf("%d: %d\t", omp_get_thread_num(), i);
        int j = i * i;
#pragma omp ordered 
        squares.push_back(j);
    }

    printf("\n");

    for(auto& v: squares) {
        printf("%d\t", v);
    }
    printf("\n");
}


TEST_CASE("Single not wait") {
#pragma omp parallel 
    {
#pragma omp single nowait 
        {
            int n;
            std::cin >> n;
            printf("Gathering input: %d\n", omp_get_thread_num());
        }
        // 这里会有一个和 single同一个线程的线程，被押后执行
        printf("In parallel on: %d\n", omp_get_thread_num());

#pragma omp barrier
#pragma omp master
        printf("Output on: %d\n", omp_get_thread_num());
    }
}