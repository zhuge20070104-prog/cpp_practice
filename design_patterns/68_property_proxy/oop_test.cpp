#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "property_proxy.hpp"
#include <utility>

#define BOOST_TEST_MODULE ProxyProperty
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestProxyProperty) {
    Creature c;
    c.strength = 11;
    int x = c.agility;
    B_LOG(info) << "c.strength = " << c.strength << "\n";
    B_LOG(info) << "c.agility = " << x << "\n";
 }

BOOST_AUTO_TEST_SUITE_END()
