#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "printer.hpp"
#include <utility>

#define BOOST_TEST_MODULE SingletonImplModule
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestSingleton) {
    Printer p1;
    int id = p1.get_id();
    
    Printer p2;
    int id2 = p2.get_id();

    std::cout << id << "\n";
    std::cout << id2 << "\n";

    BOOST_TEST(&(p1.get_id()) == &(p2.get_id()), "Address not equal");
}

BOOST_AUTO_TEST_SUITE_END()
