#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "static_template_demo.hpp"

#define BOOST_TEST_MODULE  StaticTemplateDemo
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(StaticTemplateDemoTest) {
     Chess chess;
     chess.run();
}

BOOST_AUTO_TEST_SUITE_END()
