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

// 函数模板的注意事项:
// 1. 编译器只实例化已经被调用的模板，如果不调用模板的话，模板函数不会被展开，反汇编里面看不到Max函数
// 这个过程叫模板实例化
// 2. 模板用于生成软件组件
// 3. 这些软件组件可以在不同的情况下重用
// 4. 可以操作任何数据类型
// 5. 一般用于编写高性能的算法和类
// 6. 编译时就确定，没有运行时的成本
// 7. 以下知名的库都使用了模板技术, ATL, WTL, Boost, Poco, ACE

// 函数模板
// 1. 接受模板类型参数的函数叫函数模板
// 2. 总是以template关键字开头
// 3. 模板类型参数被称做类型名
// 4. 类型名是实际类型的一个占位符
// 5. 函数模板可以接受任意类型
// 6. 模板类型可以被用做返回类型
template <typename T>
T Max(T x, T y) {
    return x>y ? x: y;
}

GTEST_TEST(TplTests, TestTemplate) {
    auto num = Max(3.3f, 5.8f);
    ASSERT_EQ(num, 5.8f);
    std::cout << num << std::endl;

    auto num2 = Max(38, 12);
    ASSERT_EQ(num2, 38);
    std::cout << num2 << std::endl;
}

