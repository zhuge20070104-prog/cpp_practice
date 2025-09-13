#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "intrusive_visitor.hpp"


#define BOOST_TEST_MODULE  IntrusiveVistor
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(IntrusiveVistorTest) {
     AdditionExpression e {
          std::make_unique<DoubleExpression>(1),
          std::make_unique<AdditionExpression>(
               std::make_unique<DoubleExpression>(2),
               std::make_unique<DoubleExpression>(3)
          )
     };

     std::stringstream ss;
     e.print(ss);
     std::cout << ss.str() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
