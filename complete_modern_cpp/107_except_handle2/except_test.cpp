#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include "gtest/gtest.h"
#include "log.hpp"


void process_records(int count) {

    if(count < 10) {
        throw std::out_of_range("Count should be greater than 10");
    }

    int *p = new int[count]; // May throw std::bad_alloc
    int* p_arr = (int*)malloc(count * sizeof(int));
    if(!p_arr) {
        throw std::runtime_error("Failed to allocate memory");
    } 

    for(int i=0; i<count; ++i) {
        p_arr[i] = i;
    }
    std::cout << "Run to here..." << std::endl;
    free(p_arr);
    delete [] p;
}

// Catch Exception的不同方式
// 1. 逐个catch已知的各种exception，比较麻烦，但是可以做个性化的定制
// 2. catch所有exception的父类std::exception，这样可以抓到所有子类异常的信息
// 3. catch ... 这样可以抓到不仅所有异常，甚至非异常的throw出的信息，但是没法确定是哪个异常，
// 第三种最好别用
GTEST_TEST(ExceptTest, CatchEachExcept) {
    try {
        process_records(5);
    }catch (std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }catch (std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
    }catch(std::bad_alloc& ex) {
        std::cout << ex.what() << std::endl;
    }
}

GTEST_TEST(ExceptTest, CatchParentExcept) {
    try {
        process_records(5);
    }catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

GTEST_TEST(ExceptTest, CatchAllError) {
    try {
        process_records(5);
    }catch(...) {
        std::cout << "Exception" << std::endl;
    }
}

