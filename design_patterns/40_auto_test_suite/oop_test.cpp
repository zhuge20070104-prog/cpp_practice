#include <iostream>
#include <string>
#include <sstream>
#include <utility>

#define BOOST_TEST_MODULE LineAdapter
#include "test.hpp"
#include "log.h"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestLineAdapter) {
    B_LOG(info) << "Hello, My boost log\n";
}

BOOST_AUTO_TEST_SUITE_END()
