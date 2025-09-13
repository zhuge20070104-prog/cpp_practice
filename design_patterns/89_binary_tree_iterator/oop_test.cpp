#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include "binary_tree_iterator.hpp"
#include "boost/foreach.hpp"

#define BOOST_TEST_MODULE BinaryTreeIterator
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(BinaryTreeIteratorTest) {
    BinaryTree<std::string> family (
        new Node<std::string>("me",        
        new Node<std::string>("Mother",
            new Node<std::string>("Mother's mother"),
            new Node<std::string>("Mother's father")),
        new Node<std::string>("father"))
    );
    
    BOOST_FOREACH(Node<std::string> const& ele, family) {
        std::cout << ele.value << "\n";
    };
}

BOOST_AUTO_TEST_SUITE_END()
