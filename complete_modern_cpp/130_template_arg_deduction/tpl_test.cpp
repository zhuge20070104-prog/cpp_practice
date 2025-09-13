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

// 函数模板推导，实例化相关
// 模板参数推导
// 1. 推导类型的过程
// 2. 每个函数参数都被检查
// 3. 相应的参数类型从调用函数的参数进行推导
// 4. 类型参数的推导应该导出相同的类型
// 5. 类型参数推导时不执行类型转换
// 6. 推导之后，模板被实例化
// 7. 可以通过在模板参数列表中指定类型参数来覆盖 类型推导
//  也就是说类型推导优先级 < 指定参数

// 模板实例化
// 1. 模板函数或者模板类仅仅只是一个蓝图
// 2. 编译器在编译期通过蓝图生成代码
// 3. 这个过程称之为模板实例化
// 4. 函数模板隐式实例化的四种情况
//  a) 函数模板被调用
//  b) 获取函数模板的地址
//  c) 显示实例化 

template <typename T>
T Max(T x, T y) {
    std::cout << typeid(T).name() << std::endl;
    return x > y ? x: y;
}

// 显示实例化char类型
template char Max(char x, char y);


GTEST_TEST(TplTests, TestOriginDeduction) {
    // 第一种类型推导为 int
    Max(3, 5); 
    // 第二种类型推导为 double
    Max(3.1, 6.2);
}


GTEST_TEST(TplTests, TestComplieError) {
    // 像下面这样写会产生编译错误，第一个参数被推导为int类型，第二个参数被推导为float类型
    // 编译器模板参数推导过程中不做任何类型转换，所以会产生编译错误
    // Max(3, 5.5f);
    Max(3.1, 6.2);
}

GTEST_TEST(TplTests, TestNoMatchFuncWorkaround) {
    // 解决方案1， 将3转换为float
    Max(static_cast<float>(3), 3.5f);
    //  解决方案2， 使用强制类型指定，替换类型推导
    Max<double>(3, 6.2); 
}

GTEST_TEST(TplTests, GetFuncAddrInst) {
    // 获取函数模板地址，将会实例化 模板函数
    int (*pfn) (int, int) = Max;
}




