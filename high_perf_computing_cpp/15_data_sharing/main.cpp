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

TEST_CASE("Data sharing no protection") {
    int i = 10;

#pragma omp parallel for 
    for(int a=0; a<10; ++a) {
        printf("thread: %d, i=%d\n", omp_get_thread_num(), i);
        i = 1000 + omp_get_thread_num();
    }
    // 最后一个线程获得的i值是最新的i值，而不是初始值
    // 结果是不确定的，因为你不知道操作系统怎么调度线程，所以你不知道最后一个线程是哪个线程
    printf("Last i: %d\n", i);
}


TEST_CASE("private i") {
    int i = 10;


    // 用private表示每个线程都有自己的i，与全局的i 不一样。
    // 不会影响全局的i
    // 每个线程的i 是独立的，也不会相互影响，
    // 每个i 里面没有初始化，装的是随机值
    // 所以各个线程会输出1000, 1001, 1002, 1003等等
    // 下面是Release模式运行的结果
    // 使用Debug模式运行程序，将会崩溃，因为i并没有被初始化，就开始使用了
#pragma omp parallel for private(i)
    for(int a=0; a<10; ++a) {
        printf("thread: %d, i=%d\n", omp_get_thread_num(), i);
        i = 1000 + omp_get_thread_num();
    }
    // private 模式不影响全局的i，最后输出10
    printf("Last i: %d\n", i);
}


TEST_CASE("firstprivate i") {
    int i = 10;
    // firstprivate，每个线程的i值被初始化为外部的i值 = 10
    #pragma omp parallel for firstprivate(i)
    for(int a=0; a<10; ++a) {
        printf("thread: %d, i=%d\n", omp_get_thread_num(), i);
        i = 1000 + omp_get_thread_num();
    }

    // 会输出第一个用于初始化的值10
    printf("Last i: %d\n", i);
}


TEST_CASE("lastprivate i") {
    int i = 10;
    #pragma omp parallel for lastprivate(i)
    for(int a=0; a<10; ++a) {
        printf("thread: %d, i=%d\n", omp_get_thread_num(), i);
        i = 1000 + omp_get_thread_num();
    }

    // lastprivate，没有初始化i，
    // 最后一个private i值，将会覆盖外部的i值
    printf("Last i: %d\n", i);
}



