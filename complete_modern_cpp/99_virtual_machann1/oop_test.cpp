#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "savings.h"
#include "transaction.h"

// 虚函数相关
// 1. 虚函数会增加一个虚函数指针的大小
// 2. 如果这个类有子类的话，析构函数也必须是虚函数，否则如果对象在堆上创建，无法析构子类对象


/**
 * 虚函数机制原理
 * 1. 不同形式的函数被提供
 * 2. 调用在编译期或运行时被处理
 * 3. 虚函数就是运行时多态或者动态绑定
 * 4. 通过虚函数机制实现
 * 5. 编译器在运行时插入代码调用正确的函数
 * 6. 通过virtual关键字自动生成
 * 7. 这些函数被称做多态函数
 * 8. 必须使用指针或引用调用
*/
GTEST_TEST(OopTest, TestInheritance) {
    std::shared_ptr<Account> saving_ptr(new Savings("Bob", 1000.0f, 0.001f));
    transact(saving_ptr.get());
    std::cout << "Size of Account: " << sizeof(Account) << std::endl;
}

