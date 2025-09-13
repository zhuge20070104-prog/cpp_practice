#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "spirit_action.hpp"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE IntepretParse
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestIntepretParse) {
    using boost::spirit::qi::int_;
    using boost::spirit::qi::parse;
    
    {
        // Example using plain function
        char const* first = "{42}", *last = first + std::strlen(first);
        parse(first, last, '{'>> int_[&client::print] >>'}');
    }

    {
        // Example using function object
        char const* first = "{43}", *last = first + std::strlen(first);
        parse(first, last, '{'>> int_[client::PrintAction()] >>'}');
    }

    {
        // Example using std::bind with a plain function
        char const* first = "{44}", *last = first + std::strlen(first);
        parse(first, last, '{' >> int_[std::bind(client::print, std::placeholders::_1)] >> '}');
    }

    {
        // Example using std::bind with a member function
        char const* first = "{45}", *last = first + std::strlen(first);
        client::Writer w;
        parse(first, last, '{' >> int_[std::bind(&client::Writer::print, &w, std::placeholders::_1)] >> '}');
    }
}

BOOST_AUTO_TEST_SUITE_END()
