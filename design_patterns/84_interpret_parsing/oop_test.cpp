#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "intepret_parse.hpp"
#include <utility>
#include <memory>

#define BOOST_TEST_MODULE IntepretParse
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestIntepretParse) {
    std::string input("(13-4)-(12+1)");
    auto tokens = lex(input);
    for(auto const& token: tokens) {
        std::cout << token << "   ";
    }
    std::cout << "\n";

    try {
        auto parsed = parse(tokens);
        std::cout << input << " = " << parsed->eval() << std::endl;
    } catch(std::exception const& ex) {
        std::cout << ex.what() << std::endl;
    }
}

BOOST_AUTO_TEST_SUITE_END()
