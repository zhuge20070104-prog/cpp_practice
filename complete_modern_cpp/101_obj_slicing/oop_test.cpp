#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "checkings.h"
#include "transaction.h"

// Object Slicing 是个什么过程
// 1. 一种编译器深思熟虑之后移除对象的一部分的情况
// 2. 当一个子类对象被赋值给基类时，会产生object-slicing
// 3. 子类对象的大小可能比基类对象要大
// 4. 当把子类赋值给基类时，内存的一部分可能会被覆盖
// 5. 这会导致内存崩坏
// 6. 为了阻止内存崩坏，编译器切分子类对象，移除子类对象自己的部分，只保留基类对象的部分
// 7. 然后把子类对象copy到基类对象里面

GTEST_TEST(OopTest, ChildObjToBasePoint) {
    Checkings ch("Bob", 100);

    Account* p_account = &ch;
    // Invoke the child's withdraw methods, can't withdraw so much
    p_account->withdraw(65);
    std::cout << p_account->get_balance() << std::endl;
    ASSERT_EQ(p_account->get_balance(), 100);
}

GTEST_TEST(OopTest, ChildObjToBaseObj) {
    Checkings ch("Bob", 100);
    Account account = ch;
    // Invoke the base's withdraw methods, can withdraw all of the money
    account.withdraw(65);
    std::cout << account.get_balance() << std::endl;
    ASSERT_EQ(account.get_balance(), 35);
}

GTEST_TEST(OopTest, ParentPtrToChildPtr) {
    Checkings ch("Bob", 100);
    Account* p_account = &ch;
    // Downcast should use dynamic cast and explictly point it
    Checkings* p_ch = dynamic_cast<Checkings*>(p_account);
    std::cout << p_ch->get_balance() << std::endl;
    p_ch->withdraw(65);
    std::cout << p_ch->get_balance() << std::endl;
    ASSERT_EQ(p_ch->get_balance(), 100);
} 

