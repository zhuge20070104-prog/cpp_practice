#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "spirit_num_list.hpp"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE IntepretNumList
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestIntepretNumList) {
    std::cout << "\t\tComma separated list parser for Spirit\n\n";
    std::cout << "Give me a comma separated list of numbers.\n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while(std::getline(std::cin, str)) {
        if(str.empty() || 'q' == str[0] || 'Q'==str[0]) {
            break;
        }

        if(client::parse_numbers(str.begin(), str.end())) {
            std::cout << "------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << str << " parses OK" << std::endl;                
        } else {
            std::cout << "------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}

BOOST_AUTO_TEST_SUITE_END()
