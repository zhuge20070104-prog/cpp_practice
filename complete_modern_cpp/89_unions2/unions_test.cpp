#include <iostream>
#include <string>
#include "gtest/gtest.h"

// 当出现非POD类型的时候， union就会变得很难用
// 必须使用inplacement new 赋值，
// 后面还要自己删除
// 推荐使用 C++ 17 std::any 或者 boost::any 替代 union，比较安全

// Rule of five 对象 A
struct A {
    A() {
        std::cout << "A::A()" << std::endl;
    }

    ~A() {
        std::cout << "A::~A()" << std::endl;
    }

    A(A const& other) {
        std::cout << "A::A(A const&)" << std::endl;
    }

    A(A&& other) noexcept {
        std::cout << "A::A(A&& other)" << std::endl;
    }

    A& operator=(A const& other) {
        std::cout << "A& A::operator=(A const& other)" << std::endl;
        if(this == &other) {
            return *this;
        }
        return *this;
    }

    A& operator=(A && other) noexcept {
        std::cout << "A& A::operator=(const&& other)" << std::endl;
        if(this == &other) {
            return *this;
        }
        return *this;
    }
};

struct B {
    B() {
        std::cout << "B::B()" << std::endl;
    }

    ~B() {
        std::cout << "B::~B()" << std::endl;
    }

    B(B const& other) {
        std::cout << "B::B(B const&)" << std::endl;
    }

    B(B&& other) noexcept {
        std::cout << "B::B(B&& other)" << std::endl;
    }

    B& operator=(B const& other) {
        std::cout << "B& B::operBtor=(B const& other)" << std::endl;
        if(this == &other) {
            return *this;
        }
        return *this;
    }

    B& operator=(B && other) noexcept {
        std::cout << "B& B::operBtor=(const&& other)" << std::endl;
        if(this == &other) {
            return *this;
        }
        return *this;
    }
};

union  UDT {
    A a;
    B b;
    std::string s;
    UDT() {

    }
    ~UDT() {

    }
};


GTEST_TEST(UnionsTest, TestStdString) {
  
    UDT udt;
    // using namespace std::string_literals;  union中没有任何对象，union是空的，不能被赋值
    // udt.s = "Hello World"s;

    new (&udt.s) std::string("Hello World");
    std::cout << udt.s << std::endl;

    ASSERT_EQ(udt.s, "Hello World");

    using std_string = std::string;
    udt.s.~std_string();
}

GTEST_TEST(UnionsTest, TestUserDefinedT) {
  
    UDT udt;
    new (&udt.a) A();
    ASSERT_EQ(typeid(udt.a), typeid(A));
    udt.a.~A();
}
