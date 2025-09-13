#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "singleton.hpp"


#define BOOST_TEST_MODULE SingletonImplModule

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestSingleton) {
    // 这里直接从生产拿数据，不合适，因为生产的数据可能会变，
    // 一旦生产的数据变了，测试用例可能会失败
    SingletonRecordFilter rf;
    std::vector<std::string> cities {"Seoul", "Mexico City"};
    int tp = rf.total_population(cities);
    BOOST_TEST(17500000 + 17400000==tp);
}

BOOST_AUTO_TEST_SUITE_END()
