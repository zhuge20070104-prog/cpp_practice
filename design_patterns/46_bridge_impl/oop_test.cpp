#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "shape.hpp"
#include <utility>

#define BOOST_TEST_MODULE Bridge
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestBridge) {
    std::unique_ptr<IRender> render(new RasterRender);
    Circle r_circle(std::move(render), 5, 5 ,5);
    r_circle.draw();
    r_circle.resize(2);
    r_circle.draw();
}

BOOST_AUTO_TEST_SUITE_END()
