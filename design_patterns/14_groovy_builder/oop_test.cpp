#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "builder.hpp"

#define BOOST_TEST_MODULE GroovyBuilder

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestGroovyBuilder) {
    using namespace html;
    std::cout << P {
        IMG {
            "https://img0.baidu.com/it/u=888809336,3658067701&fm=253&fmt=auto&app=138&f=JPEG?w=500&h=699"
        }
    } << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
