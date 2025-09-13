#include <iostream>
#include <string>
#include "gtest/gtest.h"

union  Union1 {
    int x;
    char ch;
    double d;

    Union1(): ch('a') {
        std::cout << "Union1::Union1()"<< std::endl;
    }

    ~Union1() {
        std::cout << "Union1::~Union1()" << std::endl;
    }
};


GTEST_TEST(UnionsTest, BasicUsage) {
    Union1 t;
    ASSERT_EQ(t.ch, 'a');
    t.x = 1000;
    ASSERT_EQ(t.x, 1000);
}


GTEST_TEST(UnionsTest, SizeT) {
    ASSERT_EQ(sizeof(Union1), 8);
}
