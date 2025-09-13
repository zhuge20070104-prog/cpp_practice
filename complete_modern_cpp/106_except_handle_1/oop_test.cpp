#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include "gtest/gtest.h"
#include "log.hpp"

enum ErrorCode {
    FAIL_2_ALLOC=-1,
    SUCCESS=0
};

ErrorCode process_records_no_except(int count) {
    int* p_arr = (int*)malloc(count * sizeof(int));
    if(!p_arr) {
        std::cout << "Failed to allocate memory" << std::endl;
        return FAIL_2_ALLOC;
    } 

    for(int i=0; i<count; ++i) {
        p_arr[i] = i;
    }
    std::cout << "Run to here..." << std::endl;
    free(p_arr);
    return SUCCESS;
}

ErrorCode process_records_except(int count) {
    int* p_arr = (int*)malloc(count * sizeof(int));
    if(!p_arr) {
        throw std::runtime_error("Failed to allocate memory");
    }

    for(int i=0; i<count; ++i) {
        p_arr[i] = i;
    }

    std::cout << "Run to here except" << std::endl;

    free(p_arr);
    return SUCCESS;
}

GTEST_TEST(OopTest, ProcessNoExcept) {
    process_records_no_except(std::numeric_limits<int>::max());
}

// 异常处理
// 1. 一种处理程序运行时错误的机制
// 2. 这些错误被称作异常
// 3. 异常在正常函数的外部存在
// 4. 需要程序立即进行处理
// 5. 如果不处理，程序就会crash掉
// 6. 不能被忽略，不像C的错误处理

// 异常处理语法
// 1. try { throw } catch {}
GTEST_TEST(OopTest, ProcessExcept) {
    try {
        process_records_except(std::numeric_limits<int>::max());
    } catch(std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }
}