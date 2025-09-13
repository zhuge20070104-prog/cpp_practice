#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <chrono>
#include <fstream>
#include <list>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <future>
#include <pthread.h>
#include <boost/type_index.hpp>
#define PRETTY_NAME(val)  std::cout << boost::typeindex::type_id_runtime(val).pretty_name() << std::endl;

// 直接列表初始化
// 1.  C++ 17之前，默认 花括号初始化使用auto 将会被deduce成 std::initializer_list<T>
// 2.  C++ 17之后， 直接列表初始化有两条规则了
//   a) 一个元素， deduce出来是 T
//   b) 多个元素会编译错误
// 3. 拷贝初始化，类型被deduce成std::initializer_list<T>
GTEST_TEST(TplTests, DirectListInitialization) {
    // int
    auto a {1};
    PRETTY_NAME(a)
    // 编译错误
    // auto b {1, 2};

    // std::initializer_list<int>
    auto c = {1};
    PRETTY_NAME(c)
}

// Range based for loop
// 1. Range-based for loop 允许以较容易的方式迭代range
// 2. 它自动展开成一个使用迭代器来迭代range的循环
// 3. 依赖于存在的迭代器
// 4. 直到 C++ 17之前，begin end迭代器的类型必须相同
// 5. C++ 17 允许begin/end 迭代器的类型不同，但是必须提供两种类型的!=操作符重载，用来比较结束
GTEST_TEST(TplTests, RangeBasedForLoop) {
    std::array<int, 5> values {1, 2, 3, 4, 5};
    for(auto v: values) {
        std::cout << v << " ";
    } 
    std::cout << std::endl;

    // Range based for loop 展开
    auto&& range = values;
    auto it = std::begin(range);
    auto end = std::end(range);
    for(; it!=end; ++it) {
        auto v = *it;
        std::cout << v << " ";
    }
    std::cout << std::endl;
}


// C++17中，static_assert可以有一个没有message的condition
template <typename T>
void check_pointer(T args) {
    // Error C2607, static assertion failed!
    static_assert(std::is_pointer_v<T>);
    // Error C2338, Only pointer types are allowed
    static_assert(std::is_pointer_v<T>, "Only pointer types are allowed");
}

GTEST_TEST(TplTests, StaticAssertion) {
    int x;
    // 导致assertion failure
    // check_pointer(x);
    check_pointer(&x);
}
