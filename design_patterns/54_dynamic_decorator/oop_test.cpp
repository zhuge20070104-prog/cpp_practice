#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "dynamic_decorator.hpp"
#include <utility>

#define BOOST_TEST_MODULE DynamicDecorator
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestDynamicDecorator) {
    auto square = std::make_shared<Square>(5);
    auto red_square = std::make_shared<ColoredShape>(square, "red");
    B_LOG(info) << square->str() << std::endl;
    B_LOG(info) << red_square->str() << std::endl;

    auto trans_square = std::make_shared<TransparentShape>(red_square, 51);
    B_LOG(info) << trans_square->str() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
