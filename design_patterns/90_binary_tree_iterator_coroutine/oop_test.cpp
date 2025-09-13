#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "binary_tree_iterator_coroutine.hpp"

#define BOOST_TEST_MODULE BinaryTreeIteratorCoRoutine
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(BinaryTreeIteratorCoRoutineTest) {
    BinaryTree<std::string> family (
        new Node<std::string>("me",        
        new Node<std::string>("Mother",
            new Node<std::string>("Mother's mother"),
            new Node<std::string>("Mother's father")),
        new Node<std::string>("father"))
    );

    cort_string_node::pull_type source([&](cort_string_node::push_type& sink){
        post_order<std::string>(sink, family.root);
    });

    for(auto const& node: source) {
        std::cout << node->value << std::endl;
    }
}

BOOST_AUTO_TEST_SUITE_END()
