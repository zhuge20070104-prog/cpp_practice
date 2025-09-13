#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>

#define BOOST_TEST_MODULE Iterators
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(CommonIteratorSimpleUsage) {
    using string_iterator = std::vector<std::string>::iterator;
    std::vector<std::string> names {"John", "Jane", "Jill", "Jack"};
    string_iterator it = names.begin();
    std::cout << "First name is: " << *it << std::endl;
    BOOST_TEST(*it == "John", "First name not correct!");
}

BOOST_AUTO_TEST_CASE(IteratorModify) {
    using string_iterator = std::vector<std::string>::iterator;
    std::vector<std::string> names {"John", "Jane", "Jill", "Jack"};
    string_iterator it = names.begin();
    ++it;
    it->append(std::string(" Goodall"));
    std::cout << "Second name is: " << *it << std::endl;

    BOOST_TEST(*it == "Jane Goodall", "Second name not correct after modifying!");
    string_iterator end = names.end();
    std::cout << "All names: \n"; 
    for(it = names.begin(); it != end; ++it) {
        std::cout << *it << std::endl;
    }
}


BOOST_AUTO_TEST_CASE(ReverseIterator) {
    using string_reverse_iterator = std::vector<std::string>::reverse_iterator;
    std::vector<std::string> names {"John", "Jane", "Jill", "Jack"};
    for(string_reverse_iterator ri = names.rbegin(), rend = names.rend(); ri!=rend; ++ri) {
        std::cout << *ri;
        if((ri + 1) != rend) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}


BOOST_AUTO_TEST_CASE(ConstReverseIterator) {
    using string_const_reverse_iterator = std::vector<std::string>::const_reverse_iterator;
    std::vector<std::string> names {"John", "Jane", "Jill", "Jack"};

    string_const_reverse_iterator jack = names.crbegin();
    std::cout <<*jack << std::endl;
}


BOOST_AUTO_TEST_CASE(RangeBasedForLoop) {
    std::vector<std::string> names {"John", "Jane", "Jill", "Jack"};
    for(auto&& name: names) {
        std::cout << "name= " << name << std::endl;
    }
}


BOOST_AUTO_TEST_SUITE_END()
