#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <memory>
#include "gtest/gtest.h"
#include "log.hpp"

class Test {
public:
    Test() {
        std::cout << "Test::Test() Acquiring Resources" << std::endl;
    }

    ~Test() {
        std::cout << "Test::~Test() Releasing Resources" << std::endl;
    }
};

void process_records_memory_leak(int count) {
    Test* t = new Test;
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
    delete t;
}

void process_records_good(int count) {
    std::unique_ptr<Test> t(new Test);
    if(count < 10) {
        throw std::out_of_range("Count should be greater than 10");
    }

    std::vector<int> arr;
    arr.reserve(count); // reserver 失败会 抛出std::bad_alloc异常
    for(int i=0; i<count; ++i) {
        arr.push_back(i);
    }
}


// 异常的注意点：
// 1. 栈上分配的对象，函数如果发生了异常，内部的栈还是会展开，分配的对象会被释放
// 2. 栈展开只能析构本地对象，如果对象在堆上开辟，将无法释放
// 3. 可以使用 智能指针，将 堆对象test绑定到一个栈对象std::unique_ptr，这样栈对象在栈展开时会被析构，
//    在栈对象的析构函数中，析构堆对象
// 4. 对于动态数组，可以使用std::vector替代。不要用动态数组
GTEST_TEST(ExceptTest, ProcessRecordsMemoryLeakTest) {
    try {
        process_records_memory_leak(5);
    }catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

GTEST_TEST(ExceptTest, ProcessRecordsGoodTest) {
    try {
        process_records_good(std::numeric_limits<int>::max());
        process_records_good(5);
    }catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}




