#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "array_be_property.hpp"
#include <utility>

#define BOOST_TEST_MODULE ArrayBeProperty
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestArrayBeProperty) {
    Creature c;
    c.set_strength(16);
    c.set_aglity(11);
    c.set_intelligence(9);

    B_LOG(info) << "The hero has an average state of "
        << c.average()
        << " and a maximum state of "
        << c.max()
        << "\n";
}

BOOST_AUTO_TEST_SUITE_END()
