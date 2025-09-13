#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "contact.hpp"


#define BOOST_TEST_MODULE ProtoType

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestPrototype) {
    Contact john;
    john.name = "John Doe";
    john.address = std::make_unique<Address>("123 East Dr", "London", 123);

    auto jane = clone_(john);
    jane.name = "Jane Doe";
    jane.address->street = "123B West Dr";
    jane.address->suite = 300;

    std::cout << john << std::endl;
    std::cout << jane << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
