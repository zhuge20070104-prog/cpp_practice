#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "checkings.h"
#include "transaction.h"


GTEST_TEST(OopTest, TestInheritance) {
    Checkings checking("Bob", 1000);
    transact(&checking);
}

