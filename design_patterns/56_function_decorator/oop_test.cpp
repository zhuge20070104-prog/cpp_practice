#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "function_decorator.hpp"
#include <utility>

#define BOOST_TEST_MODULE FuncDecorator
#include "test.hpp"

double add(double a, double b) {
    B_LOG(info) << a << " + " << b << " = " << (a+b) << std::endl;
    return a+b;
}

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestDecoratorFunc) {
    auto logger_add = make_logger(add, "Add");
    auto result = logger_add(2.0, 3.0);
    std::cout << "result = " << result << "\n";
}

BOOST_AUTO_TEST_SUITE_END()
