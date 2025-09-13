#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "shape.hpp"
#include <utility>

#define BOOST_TEST_MODULE Composite
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestComposite) {
    auto root = std::make_shared<Group>("root");
    auto c1 = std::make_shared<Circle>();
    auto c2 = std::make_shared<Circle>();
    root->graphics.push_back(c1);

   auto sub_group = std::make_shared<Group>("sub");
    sub_group->graphics.push_back(c2);
    root->graphics.push_back(sub_group);
    root->draw();
}

BOOST_AUTO_TEST_SUITE_END()
