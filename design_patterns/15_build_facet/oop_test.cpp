#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "person.hpp"

#define BOOST_TEST_MODULE BuildFacet

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestBuilderFacet) {
    Person p = Person::create().lives().at("渥太华公寓").with_post_code("342200").in("Ottwa").works().at("Telenav").
        as_a("Staff QA Engineer").earning(3000);
    std::cout << p << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
