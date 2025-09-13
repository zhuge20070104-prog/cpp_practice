#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "text_formatter.hpp"
#include <utility>

#define BOOST_TEST_MODULE Formatter
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestFormatter) {
    FormatterText ft {"This is a brave new world"};
    ft.capitalise(10, 15);
    // 大写brave字符串
    std::cout << ft << std::endl;

    BetterFormatterText bft {"This is a brave new world"};
    bft.get_range(10, 15).capitalise = true;
    // 大写brave字符串
    std::cout << bft << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
