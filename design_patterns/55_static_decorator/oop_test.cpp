#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "static_decorator.hpp"
#include <utility>

#define BOOST_TEST_MODULE StaticDecorator
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestStaticDecorator) {
    ColoredShape<Circle> greep_circle {"green", 5};
    B_LOG(info) << greep_circle.str() << std::endl;

    TransparentShape<ColoredShape<Square>> blue_invisible_square {0, "blue", 10};
    blue_invisible_square.color = "blue";
    blue_invisible_square.side = 321;
    B_LOG(info) << blue_invisible_square.str() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
