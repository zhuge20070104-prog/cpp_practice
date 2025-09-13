#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "savings.h"


GTEST_TEST(OopTest, TestInheritance) {
    Account acc("Bob", 1000);
    ASSERT_EQ(acc.get_balance(), 1000);
    acc.deposit(200);
    ASSERT_EQ(acc.get_balance(), 1200);
    acc.withdraw(380);
    ASSERT_EQ(acc.get_balance(), 820);
}

