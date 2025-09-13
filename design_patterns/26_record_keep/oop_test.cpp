#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "contact.hpp"


#define BOOST_TEST_MODULE AbstractFactory

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestAbstractFactory) {
    Contact john {"John Doe", Address{"123 East Dr", "London", 123}};
    // 拷贝构造函数深拷贝
    Contact jane = john; 

    jane.name = "Jane Smith";
    jane.address.suite = 103;
    std::cout << john << std::endl;
    std::cout << jane << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
