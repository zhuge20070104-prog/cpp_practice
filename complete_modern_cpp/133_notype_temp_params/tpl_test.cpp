#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"

// 非类型模板参数
// 1. 模板参数列表中在编译期计算的表达式
// 2. 必须是一个常量表达式，在编译期能确定的表达式[变量地址，函数地址，引用，整型，null_ptr,枚举等等]
// 3. 他是模板类型的一部分
// 4. std::begin和std::end函数使用了非类型模板参数

template <std::size_t size> 
void print() {
    // 编译期常量可以用来指定数组大小
    char buffer[size];
    std::cout << size << std::endl;
}


template <std::size_t size> 
void print_change_size() {
    // 非类型化的模板参数是一个常量，不能在函数中进行修改，这样搞会编译错误
    // ++size;
    char buffer[size];
    std::cout << size << std::endl;
}

template <typename T>
T sum(T* p_arr, std::size_t size) {
    T res {};
    for(std::size_t i=0; i<size; ++i) {
        res += p_arr[i];
    }
    return res;
}

template <typename T, std::size_t size>
T sum2(T (&p_arr)[size]) {
    T res {};
    for(std::size_t i=0; i<size; ++i) {
        res += p_arr[i];
    }
    return res;
}


GTEST_TEST(TplTests, TestNonTypeParam) {
    print<3>();
}

GTEST_TEST(TplTests, TestPassNonConst) {
   // 使用非常量编译错误
    std::size_t size = 3;
    // print<size>();
}

GTEST_TEST(TplTests, TestPassSizeofConst) {
   //  sizeof 编译期可计算，可行
    std::size_t size = 3;
    print<sizeof(size)>();
}


GTEST_TEST(TplTests, TestChangeSizeInPrint) {
    print_change_size<3>();
}

GTEST_TEST(TplTests, TestSum1) {
    int arr[] = {3, 1, 9, 7};
    int sum_r = sum(arr, 4);
    std::cout << sum_r << std::endl;
    ASSERT_EQ(sum_r, 20);
}

GTEST_TEST(TplTests, TestSum2) {
    int arr[] = {3, 1, 9, 7};
    int sum_r = sum2(arr);
    std::cout << sum_r << std::endl;
    ASSERT_EQ(sum_r, 20);
}



