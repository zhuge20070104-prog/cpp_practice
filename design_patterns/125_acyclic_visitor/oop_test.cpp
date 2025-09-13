#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>

#include "acyclic_visitor.hpp"


#define BOOST_TEST_MODULE  AcyclicVisitor
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(AcyclicVisitorTest) {
     AdditionExpression e {
          std::make_unique<DoubleExpression>(1),
          std::make_unique<SubstractionExpression>(
               std::make_unique<DoubleExpression>(3),
               std::make_unique<DoubleExpression>(2)
          )
     };

     ExpressionPrinter ep;
     ExpressionEvaluator ee;
     ep.visit(e);
     ee.visit(e);
     std::cout << ep.str() << "=" << ee.result << "\n";
}

BOOST_AUTO_TEST_SUITE_END()
