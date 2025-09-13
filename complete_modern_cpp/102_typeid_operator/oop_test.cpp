#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include "gtest/gtest.h"
#include "checkings.h"
#include "savings.h"
#include "transaction.h"

#define LOG(...) \
    std::stringstream ss;\
    ss << "LOG: " <<  __FILE__ << ":" << __LINE__ << " [Function] " << __FUNCTION__ << ": " << std::endl; \
    for(auto const& msg: {__VA_ARGS__})  { \
        ss  << msg << std::endl;  \
    } \
    std::cout << ss.str() << std::endl; \



GTEST_TEST(OopTest, TypeidBasics) {
    int i{};
    std::type_info const& ti = typeid(i);
    std::cout << "Type name: " << ti.name() << std::endl;
    ASSERT_EQ(typeid(i), typeid(int));
}


GTEST_TEST(OopTest, TypeidObjects) {
    Savings ch("Bob", 100, 0.05f);
    Account* p = &ch;
    std::type_info const& ti = typeid(*p);
    std::cout << "Type name: " <<  ti.name() << std::endl;
    ASSERT_EQ(typeid(*p), typeid(Savings));
}

// typeid + static cast的方式，也可以用dynamic_cast替换，
// 如果父类型可以转换为子类型，返回子类型
// 否则返回nullptr
// 返回nullptr时，直接判空就可以
GTEST_TEST(OopTest,  DynamicCastPointer) {
    Checkings checkings("Bob", 180, 50);
    transact(&checkings); 
}

// dynamic_cast也可以处理引用，但是引用不能为空
// 如果引用转换失败会抛出一个std::bad_cast异常
GTEST_TEST(OopTest,  DynamicCastRef) {
    Savings savings("Bob", 100, 0.05f);
    try {
        transact(savings); 
    } catch (std::exception const& ex) {
        LOG("Exception occurred", ex.what())
    }
}
   


