#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "moment_to.hpp"

#define BOOST_TEST_MODULE  MomentTo
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(MomentToTest) {
    BankAccount ba {100};
    auto m1 = ba.deposit(50); // 150
    auto m2 = ba.deposit(25); // 175

    std::cout << ba << "\n";
    ba.restore(m1);
    std::cout << "Back to m1: " << ba << "\n";

    ba.restore(m2);
    std::cout << "Back to m2: " << ba << "\n";
}

BOOST_AUTO_TEST_SUITE_END()
