#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "spirit_roman.hpp"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE IntepretNumList
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestIntepretNumList) {
    namespace qi = boost::spirit::qi;

    using iterator_type = std::string::const_iterator;
    using roman_type = client::roman<iterator_type>;

    std::cout << "\t\tRoman Number Parser\n\n";
    std::cout << "Type a Roman Numeral.\n";
    std::cout << "Type [q or Q] to quit\n\n";

    // 语法树对象
    roman_type roman_parser;
    std::string str;
    unsigned result {0};
    while(std::getline(std::cin, str)) {
        if(str.empty() || 'q' == str[0] || 'Q'==str[0]) {
            break;
        }

        std::vector<double> v;
        iterator_type iter = str.begin();
        iterator_type end = str.end(); 
        bool r = qi::parse(iter, end, roman_parser, result);
        if(r && iter == end) {
            std::cout << "------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "Result = " << result << std::endl;  
            std::cout << "------------------------\n";              
        } else {
            std::string rest {iter, end};
            std::cout << "------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "Stopped at: \"" << rest << "\"\n";
            std::cout << "------------------------\n";
        }
    }
    std::cout << "Bye...\n\n";
}

BOOST_AUTO_TEST_SUITE_END()
