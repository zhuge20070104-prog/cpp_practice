#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "dynamic_strategy.hpp"

#define BOOST_TEST_MODULE  DynamicStrategy
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(DynamicStrategyTest) {
     // markdown
     TextProcessor tp;
     tp.set_output_format(OutputFormat::Markdown);
     tp.append_list({"Good", "Bad", "Excellent"});
     std::cout << tp.str() << std::endl;

     // Html
     tp.clear();
     tp.set_output_format(OutputFormat::Html);
     tp.append_list({"Good", "Bad", "Excellent"});
     std::cout << tp.str() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
