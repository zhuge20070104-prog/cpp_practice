#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "spirit_complex.hpp"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE IntepretComplex
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestIntepretComplex) {
    std::cout << "////////////////////////////////////////\n\n";
    std::cout << "A complex number micro parser for spirit\n\n";
    std::cout << "////////////////////////////////////////\n\n";

    std::cout << "Give me a complex number of the form r or (r) or (r,i) \n";
    std::cout << "Type [q or Q] to quit\n\n";

    std::string str;
    while(std::getline(std::cin, str)) {
        if(str.empty() || str[0] == 'q' || str[0] == 'Q') {
            break;
        }

        std::complex<double> c;
        if(client::parse_complex(str.begin(), str.end(), c)) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "Got: " << c << std::endl;
            std::cout << "-------------------------\n";
        } else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "Bye...\n\n";
}

BOOST_AUTO_TEST_SUITE_END()
