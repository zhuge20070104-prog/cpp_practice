#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "contact.hpp"


#define BOOST_TEST_MODULE ProtoType

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestPrototype) {
    auto john = EmployeeFactory::new_main_office_employee("John Doe", 123);
    auto jane = EmployeeFactory::new_main_office_employee("Jane Smith", 103);

    std::cout << *john << std::endl;
    std::cout << *jane << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
