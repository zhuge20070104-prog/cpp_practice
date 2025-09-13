#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "reflective_visitor.hpp"


#define BOOST_TEST_MODULE  ReflectiveVisitor
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(ReflectiveVisitorTest) {
     AdditionExpression e {
          std::make_unique<DoubleExpression>(1),
          std::make_unique<AdditionExpression>(
               std::make_unique<DoubleExpression>(2),
               std::make_unique<DoubleExpression>(3)
          )
     };

     ExpressionPrinter ep;
     ep.print(&e);
     std::cout << ep.str() << "\n";
}

BOOST_AUTO_TEST_SUITE_END()
