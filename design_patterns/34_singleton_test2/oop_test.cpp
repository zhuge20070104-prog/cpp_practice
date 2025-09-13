#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "singleton.hpp"


#define BOOST_TEST_MODULE SingletonImplModule

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestSingleton) {
    // 上面这一节是生产数据，不要这么写
    auto& db= SingletonDatabase::get();  
    ConfigurableRecordFilter rf(db);
    int tp = rf.total_population({"Seoul", "Mexico City"});
    std::cout << "Soeul, Mexico City Total Population: " << tp << std::endl; 

    DummyDatabase dummy_db;
    ConfigurableRecordFilter dummy_rf(dummy_db);
    std::vector<std::string> cities {"alpha", "gamma"};
    int dummy_tp = dummy_rf.total_population(cities);
    BOOST_TEST(1 + 3 == dummy_tp, "Dummy population test failed");
}

BOOST_AUTO_TEST_SUITE_END()
