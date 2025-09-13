#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "drawer.hpp"
#include <utility>

#define BOOST_TEST_MODULE LineAdapter
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestLineAdapter) {
    DrawableObjects objs {
        std::make_shared<VectorRectangle>(10, 10, 100, 100),
        std::make_shared<VectorRectangle>(30, 30, 60, 60)
    };

    Drawer d {objs};
    d.draw();
    d.wait_for_dispose();
}

BOOST_AUTO_TEST_SUITE_END()
