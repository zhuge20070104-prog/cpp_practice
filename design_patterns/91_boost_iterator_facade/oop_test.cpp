#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include <boost/foreach.hpp>
#include "boost_iterator_facade.hpp"

#define BOOST_TEST_MODULE   ListIterator
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(ListIteratorTest) {

    string_list  list;
    list.add("alpha");
    list.add("beta");
    list.add("gamma");

    std::cout << "Use range based for loop: \n";
    for(auto const& ele: list) {
        std::cout << ele.value << std::endl;
    }

    std::cout << "Use std::for_each: \n";
    std::for_each(list.begin(), list.end(), [](Node<std::string> const& ele) {
        std::cout << ele.value << "\n";
    });
}

BOOST_AUTO_TEST_SUITE_END()
