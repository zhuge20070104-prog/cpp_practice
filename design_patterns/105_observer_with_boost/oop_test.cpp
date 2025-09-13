#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "observer_with_boost.h"

#define BOOST_TEST_MODULE  ObserverWithBoost
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(ObserverWithBoostTest) {
    Person p (20);
    p.set_age(23);
}

BOOST_AUTO_TEST_SUITE_END()
