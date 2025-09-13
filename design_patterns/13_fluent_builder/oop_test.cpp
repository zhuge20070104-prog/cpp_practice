#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "builder.hpp"

#define BOOST_TEST_MODULE FluentBuilder

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestFluentBuilder) {
    HTMLElement ele = HTMLBuilder::create("ul").add_child("li", "hello")
        .add_child("li", "world");
    
    std::cout << ele.str() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
