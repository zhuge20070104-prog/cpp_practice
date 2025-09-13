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


class A {
public:
    A() {
        std::cout << "A::A()" << std::endl;
    }

    ~A() {
        std::cout << "A::~A()" << std::endl;
    }
 };

class B {
public:
    B() {
        std::cout << "B::B()" << std::endl;
    }

    ~B() {
        std::cout << "B::~B()" << std::endl;
    }
 };

class ATest {
private:
    A* p_a{};
    B b {};
    int* p_int{};
    char* p_str{};
    int* p_arr{};

public:
    ATest() {
        std::cout << "ATest::ATest() Acquiring Resources" << std::endl;
        p_a = new A;
        p_int = new int;
        throw std::runtime_error("Fail to initialize");
        p_str  = new char[100];
        p_arr = new int[50];
    }

    ~ATest() {
        std::cout << "ATest::~ATest() Releasing Resources" << std::endl;
        delete p_a;
        delete p_int;
        delete []p_str;
        delete []p_arr;
    }
};


class ATestGood {
private:
    std::unique_ptr<A> p_a{};
    B b {};
    std::unique_ptr<int> p_int{};
    std::string p_str{};
    std::vector<int> p_arr{};

public:
    ATestGood() {
        std::cout << "ATestGood::ATestGood() Acquiring Resources" << std::endl;
        p_a.reset(new A);
        p_int.reset(new int);
        throw std::runtime_error("Fail to initialize");
        
    }

    ~ATestGood() {
        std::cout << "ATestGood::~ATestGood() Releasing Resources" << std::endl;
    }
};

class ATestDesBad {
private:
    std::unique_ptr<A> p_a{};
    B b {};
    std::unique_ptr<int> p_int{};
    std::string p_str{};
    std::vector<int> p_arr{};

public:
    ATestDesBad() {
        std::cout << "ATestDesBad::ATestDesBad() Acquiring Resources" << std::endl;
        p_a.reset(new A);
        p_int.reset(new int);    
    }

    ~ATestDesBad() {
        std::cout << "ATestDesBad::~ATestDesBad() Releasing Resources" << std::endl;
        throw std::runtime_error("Fail to release memory");
    }
};


GTEST_TEST(ExceptTest,  ExceptConstBad) {
    try {
        ATest t;
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }
}

// 构造函数中的异常导致对象内存无法释放的问题。可以使用智能指针解决
GTEST_TEST(ExceptTest,  ExceptConstGood) {
    try {
        ATestGood t;
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }
}


// 析构函数中不要抛出异常
//  因为析构函数中的异常可能和主程序中的其他异常一起抛出来
// 导致try catch block中出现多个异常，
// 程序优先捕获try-catch block中的异常
// 无法捕获析构函数的异常
// 导致程序崩溃
GTEST_TEST(ExceptTest,  ExceptDesBad) {
    try {
        ATestDesBad t;
        throw std::runtime_error("Exception");
    }catch (std::runtime_error& ex) {
        LOG(std::cout, ex.what())
    }

    LOG(std::cout, "Can't go here");
}




