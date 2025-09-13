#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "fly_weight.hpp"
#include <utility>

#define BOOST_TEST_MODULE ManualFlyWeight
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestManualFlyWeight) {
    User user1 {"John", "Smith"};
    User user2 {"Jane", "Smith"};
    std::cout << user1 << std::endl << user2 << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
