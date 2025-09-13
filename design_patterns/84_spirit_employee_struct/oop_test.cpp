#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "spirit_emp_struct.hpp"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE IntepretEmployee
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestIntepretEmployee) {
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tAn Employee parser for Spirit...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Give me an Employee of the form :"
        << "Employee{age, \"surname\", \"forename\", salary } \n";
    std::cout << "Type [q or Q] to quit\n\n";

    namespace qi = boost::spirit::qi;
    using boost::spirit::ascii::space;
    using iterator_type = std::string::const_iterator;
    using EmployeeParser = client::EmployeeParser<iterator_type>;
    
    std::string str;
    EmployeeParser g;

    while(std::getline(std::cin, str)) {
        if(str.empty() || str[0] == 'q' || str[0] == 'Q') {
            break;
        }

        client::Employee emp;
        iterator_type start = str.begin();
        iterator_type end = str.end();

        bool r = qi::phrase_parse(start, end, g, space, emp);
        if(r && start == end) {
            std::cout << boost::fusion::tuple_open('[');
            std::cout << boost::fusion::tuple_close(']');
            std::cout << boost::fusion::tuple_delimiter(", ");

            std::cout << "------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << boost::fusion::as_vector(emp) << std::endl;
            std::cout << "------------------------\n";
        } else {
            std::cout << "------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "------------------------\n";
        }
    }

    std::cout << "Bye...\n\n";
}

BOOST_AUTO_TEST_SUITE_END()
