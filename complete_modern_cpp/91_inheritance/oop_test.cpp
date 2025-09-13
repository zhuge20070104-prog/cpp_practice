#include <iostream>
#include <string>
#include "gtest/gtest.h"

// 关于OOP中的继承和组合
// 1. 系统是由对象组成的
// 2. 对象是类的实例
// 3. 类和对象是相关的
// 4. 对象之间相互协作
// 5. 定义系统行为
// 组合
// 1. 对象组合在另一个对象中
// 2. 是一种has a的关系
// 3. 重用行为和方法
// 继承
// 1. 类继承另外一个类的特性
// 2. 重用，继承行为
// 3. 是一种is a的关系
class Animal {
public:
    virtual void eat() {
        std::cout << "Animal eating..." << std::endl;
    }

    virtual void run() {
        std::cout << "Animal running..." << std::endl;
    }

    virtual void speak() {
        std::cout << "Animal speaking..." << std::endl;
    }
};

class Dog: public Animal {
public:
    void eat() override {
        std::cout << "Dog eating meat..." << std::endl; 
    }

    void speak() override {
        std::cout << "Dog barking..." << std::endl;
    }
};

GTEST_TEST(UnionsTest, TestStdString) {
    Dog d;
    d.eat();
    d.run();
    d.speak();
}

