#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "singleton.hpp"


#define BOOST_TEST_MODULE SingletonImplModule

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestSingleton) {
    std::string city = "Tokyo";
    auto& db =  SingletonDatabase::get();
    std::cout << city << " has population: "
        << db.get_population(city)
        << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
