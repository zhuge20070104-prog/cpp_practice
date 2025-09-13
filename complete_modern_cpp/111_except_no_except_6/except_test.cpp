#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <random>
#include "gtest/gtest.h"
#include "log.hpp"

// noexcept标记的要点
// 1. 应用到函数，声明和定义都要应用
// 2. 表明这个函数不会抛出异常
// 3. 编译器会优化函数代码，不会生成栈展开的代码
// 4. 从noexcept 函数里面抛异常会导致程序崩溃，栈可能展开也可能不会展开
// 5. 并非所有函数都需要标记为noexcept
//  a. 库函数不能被标记为noexcept，因为你不知道它会不会抛出异常

// 移动构造函数和移动赋值操作符需要被指定为noexcept,
// 因为STL 容器在调用移动构造函数和移动赋值操作符时，会先检查你的移动构造和移动赋值是否被标记为noexcept(true)
// 他们默认只会调用标记为noexcept(true)的移动构造和移动赋值操作符

class A {
public:
    A() {
        std::cout << "A::A()" << std::endl;
    }

    ~A() {
        std::cout << "A::~A()" << std::endl;
        throw 3;
    }
};

// noexcept 接受一个boolean参数， 代表sum会不会throw,
// 如果参数为true, 代表它不会throw，如果参数为false,代表它会throw,
// 这里表示这个函数不会throw
int sum(int x, int y) noexcept(true) {
    return x+y;
}

// No except的函数throw会导致程序崩溃
int sum_no_except_throw(int x, int y)  noexcept(true){
    throw 3;
    return x+y;
}


void test(int x) {
    throw x;
}

// sum会去调用 test, test会throw
// 这样sum还是会throw,
// 而mark sum函数为noexcept还是会导致程序崩溃
int sum_nested_throw(int x, int y) noexcept(true) {
    test(x);
    return x+y;
}

// noexcept 设置为false，可能throw，也可能不throw
// 这样不会crash，因为编译器会做栈展开
int sum_no_except_false_throw(int x, int y) noexcept(false) {
    test(x);
    return x + y;
}

// noexcept嵌套
// 因为test没有指定,test的noexcept属性是false，可以抛异常
// 那么sum取的是test的noexcept属性，也是false，可以抛异常，不会崩溃
int sum_no_except_nested(int x, int y) noexcept(noexcept(test(x))) {
    test(x);
    return x + y;
}

// std::cout<< 是一个库函数，我们不能保证它是否抛出异常
// 所以这里我们说noexcept(false),表示可能产生异常
void test_std_cout(int x) noexcept(false) {
    std::cout << x << std::endl;
}

GTEST_TEST(ExceptTest,  ExceptNoExceptBasic) {
    try {
        sum(3, 5);
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }
}


GTEST_TEST(ExceptTest,  ExceptNoExceptThrow) {
    // Dont do like this, mark a function as no except then throw an exception from it
    try {
        // sum_no_except_throw(3, 5);
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }
}


GTEST_TEST(ExceptTest,  ExceptNoExceptThrowNested) {
    // Dont do like this, mark a function as no except then throw an exception from it
    try {
        // sum_nested_throw(3, 5);
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }
}


GTEST_TEST(ExceptTest,  ExceptNoExceptFalseThrow) {
    // Dont do like this, mark a function as no except then throw an exception from it
    try {
        sum_no_except_false_throw(3, 5);
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }
}


GTEST_TEST(ExceptTest,  ExceptNoExceptNestedCal) {
    // Dont do like this, mark a function as no except then throw an exception from it
    try {
        sum_no_except_nested(3, 5);
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }
}

GTEST_TEST(ExceptTest,  ExceptNoExceptOperator) {
    LOG(std::cout, std::boolalpha, "Noexcept of test(5): ", noexcept(test(5)))
}

GTEST_TEST(ExceptTest,  ExceptNoExceptLibrary) {
    test_std_cout(10);
}

// Don't throw any exception from destructors, since they're guaranteed as noexcept by default in C++11
GTEST_TEST(ExceptTest,  ExceptNoExceptDestructDefault) {
    // A a;
    // LOG(std::cout, std::boolalpha, "Noexcept of a.~A()", noexcept(a.~A()))
}






