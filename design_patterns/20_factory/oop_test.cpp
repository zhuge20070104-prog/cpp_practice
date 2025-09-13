#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "point.hpp"


#define BOOST_TEST_MODULE Factory

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestFactory) {
    auto p = PointFactory::NewPolar(5.0f, (float)M_PI_4);
    std::cout << p << std::endl;
    BOOST_TEST(p.x == 3.53553, boost::test_tools::tolerance(0.00001));
    BOOST_TEST(p.y == 3.53553, boost::test_tools::tolerance(0.00001));
}

BOOST_AUTO_TEST_SUITE_END()
