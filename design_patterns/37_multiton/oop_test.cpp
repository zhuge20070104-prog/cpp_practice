#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "multiton.hpp"
#include <utility>

#define BOOST_TEST_MODULE MultitonImplModule
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestMultiton) {
    auto main = MultitonPrinter::get(Importance::Primary);
    auto aux = MultitonPrinter::get(Importance::Secondary);
    auto aux2 = MultitonPrinter::get(Importance::Tertiary);

    auto small = MultitonCircle::get(Size::Small);
    auto medium = MultitonCircle::get(Size::Medium, 2.0f);
    auto large = MultitonCircle::get(Size::Large, 3.0f);
}

BOOST_AUTO_TEST_SUITE_END()
