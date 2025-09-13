#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include <utility>

#define BOOST_TEST_MODULE StringTest
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestString) {
    std::string s =  R"(/api/pingpong/(.*))";
    if(s.find(R"((.*))")!=std::string::npos) {
        std::cout << "Found\n";
    } else {
        std::cout << "Not found\n";
    }
}

BOOST_AUTO_TEST_SUITE_END()
