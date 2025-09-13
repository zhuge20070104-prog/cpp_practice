#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "virtual_proxy.hpp"
#include <utility>

#define BOOST_TEST_MODULE VirtualProxy
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestVirtualProxy) {
    LazyBitmap bmp {"pokenman.png"};
    bmp.draw();
    bmp.draw();
 }

BOOST_AUTO_TEST_SUITE_END()
