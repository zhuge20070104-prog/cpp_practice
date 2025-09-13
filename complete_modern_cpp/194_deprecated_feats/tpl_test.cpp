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



GTEST_TEST(TplTests, DeprecatedFeatures) {
    // register 关键字
    // 1. 一个标记标记当前变量需要被存储在寄存器里面
    // 2. 这种存储类型在 C++11中被移除
    // 3. 这个关键字现在对程序的语义没有任何影响
    // 现代编译器会自动优化寄存器存储，不需要register关键字
    // void register_keyword() {
    //  register int x;
    //  x = 5;
    // }

    // operator ++ (bool)
    // 1. bool类型上面的++操作符被移除了
    // 2. bool 类型上面的 -- 操作符从来没有被允许过
    // bool x {};
    // x++;


    // 特殊字符的转义字符
    // 1. 当一个系统不支持7位的ascii时，使用的特殊字符的转义字符去掉了
    // 特殊字符的转义不需要了，因为现代键盘支持特殊字符了
    // 2. 例如?? --> 生成 --> ~
    // 3. 这些被移除用来加速编译进程

    
    // 异常指定
    // 1. 允许函数指定他 throw了哪些异常的特性
    // 2. 许多编译器都没有实现该特性
    // 3. 使用 noexcept 进行替代
    // void check(int a) throw(int) {
    //       if(a > 1000) {
    //            throw 1;
    //        }
    //    }


    // std::auto_ptr
    // 1. C++ 98 智能指针
    // 2. 没有owner ship的语义
    // 3. 可能导致bug
    // 4. 使用std::unique_ptr和std::shared_ptr替代


    // 库函数
    // 1. std::random_shuffle
    // 依赖于C的random函数，被std::random算法替代
    // 2. std::unary_function 和 std::ptr_fun
    // 使用std::function<T> 取代
    // 3. std::bind1st 
    // 使用std::bind 替代    
}
