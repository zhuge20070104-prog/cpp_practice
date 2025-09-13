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

// 模板特化相关
// 1. 特定类型的模板特化
// 2. 为一些特定数据类型提供正确的语义
// 3. 或者为指定数据类型做算法优化
// 4. 显示特化函数必须在.cpp文件中定义，显示特化函数已经被实例化，必须被定义在cpp文件中，否则就会出现头文件一份，实现文件一份，两份拷贝
// 5. 主模板函数需要在特化函数之前定义

// 主模板
template <typename T>
T Max(T a, T b) {
    std::cout << typeid(T).name() << std::endl;
    return a > b? a: b;
}

// 显示实例化
template char Max(char x, char y);

// 显示特化
// 为什么要对 char const* 做显示特化，因为 char const* 是指针类型
// 默认比较指针地址大小，与我们期望的输出不符，所以需要显示特化一下

// Max后面那个 char const*类型可加可不加，建议加上，和模板实例化区分开
template <>
char const* Max<char const*>(char const* x, char const* y) {
    std::cout << "Max<char const*>()" << std::endl;
    return strcmp(x, y) > 0 ? x: y;
}

GTEST_TEST(TplTests, TestExplicitSpecilization) {
    char const* a {"A"};
    char const* b {"B"};
    auto s = Max(a, b);
    ASSERT_EQ(s, "B");
    std::cout << s << std::endl;
}
