#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "drink.hpp"


#define BOOST_TEST_MODULE AbstractFactory

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestAbstractFactory) {
    DrinkFactory df;
    df.make_drink(DrinkType::Coffe);
    df.make_drink(DrinkType::Tea);
}

BOOST_AUTO_TEST_SUITE_END()
