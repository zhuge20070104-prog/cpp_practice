#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "intepret_lex.hpp"
#include <utility>
#include <memory>

#define BOOST_TEST_MODULE Lex
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestLex) {
    std::string input("(13-4)-(12+1)");
    auto tokens = lex(input);
    for(auto const& token: tokens) {
        std::cout << token << "   ";
    }
    std::cout << "\n";
}

BOOST_AUTO_TEST_SUITE_END()
