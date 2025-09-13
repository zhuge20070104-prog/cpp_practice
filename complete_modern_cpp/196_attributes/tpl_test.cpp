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
#include "a.h"
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <future>
#include <pthread.h>
#include <boost/type_index.hpp>
#define PRETTY_NAME(val)  std::cout << boost::typeindex::type_id_runtime(val).pretty_name() << std::endl;


// Attributes 属性
// 1. 属性是编译器相关的命令，用来给编译器额外的信息
// 2. 他们被用来做优化，或者检查
// 3. 在C++11之前，不同的编译器厂商使用不同的属性，例如MSVC使用__declspec, GCC使用__attribute
// 4. C++11引入一些标准的属性，这些属性在所有标准兼容的编译器上面都可用
// 5. C++ 14和C++17引入了更多的属性

// 程序员不能够创建自定义属性
// 通用属性列表请查看 images/attributes.png


[[deprecated("Use the new function instead")]]
int* create_int_array(std::size_t size) {
    return new int[size];
}

// 这个deprecated必须放在class关键字后面
// 否则会被忽略
class [[deprecated("This class is deprecated, use the NewTest class instead")]] MyTest {

};


template <typename T>
[[nodiscard]]
T* create_array(std::size_t size) {
    return new T[size];
}

// 类类型也可以nodiscard
class [[nodiscard]] Number {

};

Number get_number(int x) {
    return Number{};
}

// 使用过期函数，会被当做警告或者错误处理
GTEST_TEST(TplTests, DeprecatedFunc) {
    create_int_array(3);
}


// Class 也可以Deprecated
GTEST_TEST(TplTests, DeprecatedClass) {
    MyTest t;
}

// namespace 也可以Deprecated
// gcc 忽略namespace deprecated
GTEST_TEST(TplTests, DeprecatedNamespace) {
    A::MyEle ele;
}

// 一定要使用返回值，不能忽略，否则会产生警告
GTEST_TEST(TplTests, NoDiscardFunc) {
    create_array<int>(3);
}


GTEST_TEST(TplTests, NoDiscardClass) {
    get_number(3);
}


