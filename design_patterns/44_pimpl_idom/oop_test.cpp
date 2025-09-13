#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "person.h"
#include <utility>

#define BOOST_TEST_MODULE PImpl
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestPImpl) {
    Person p{"张三"};
    p.greet();
}

BOOST_AUTO_TEST_SUITE_END()
