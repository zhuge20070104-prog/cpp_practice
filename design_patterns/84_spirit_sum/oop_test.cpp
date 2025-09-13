#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "spirit_sum.hpp"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE IntepretNumList
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestIntepretNumList) {
    std::cout << "\t\tComma separated list parser for Spirit\n\n";
    std::cout << "Give me a plus separated list of numbers.\n";
    std::cout << "The numbers are added using Phoenix\n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while(std::getline(std::cin, str)) {
        if(str.empty() || 'q' == str[0] || 'Q'==str[0]) {
            break;
        }

        double n {0.0};
        if(client::adder(str.begin(), str.end(), n)) {
            std::cout << "------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << " parses OK" << std::endl;         
            std::cout << str << "=" << n << std::endl;
        } else {
            std::cout << "------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}

BOOST_AUTO_TEST_SUITE_END()
