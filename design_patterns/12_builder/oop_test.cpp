#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "builder.hpp"

#define BOOST_TEST_MODULE BuilderModule

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())



BOOST_AUTO_TEST_CASE(TestBuilder) {
    HTMLBuilder builder {"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    std::cout << builder.str() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
