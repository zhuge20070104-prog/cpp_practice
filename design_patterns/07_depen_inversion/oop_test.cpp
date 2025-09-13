#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "person.hpp"

#define BOOST_TEST_MODULE DependencyInvertion

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())



BOOST_AUTO_TEST_CASE(TestPersonRelationship) {
    Person parent {"John"};
    Person child1 {"Chris"}, child2 {"Matt"};

    std::unique_ptr<RelationShips> rels{new RelationShips};
    rels->add_parent_and_child(parent, child1);
    rels->add_parent_and_child(parent, child2);

    RSearch r_search(std::move(rels));
    r_search.search_child("John");    
}

BOOST_AUTO_TEST_SUITE_END()
