#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "checkings.h"


GTEST_TEST(OopTest, TestInheritance) {
    Checkings acc("Bob", 600);
    ASSERT_EQ(acc.get_balance(), 600);
    acc.withdraw(551);
    ASSERT_EQ(acc.get_balance(), 49);
    // Withdraw should be failed here
    acc.withdraw(40);
    ASSERT_EQ(acc.get_balance(), 49);
}

