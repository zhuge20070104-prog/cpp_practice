#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "property_tree_xml.h"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE PropertyTreeJson
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestPropertyTreeJsonLoad) {
    client::debug_settings debug_set("../debug_settings.xml");
    debug_set.load();
    
    std::cout << "Log file path: " << debug_set.m_file << std::endl;
    std::cout << "Log level: " << debug_set.m_level << std::endl;
    std::cout << "Modules enabled log: \n";
    for(auto const& module: debug_set.m_modules) {
        std::cout << module << "\t";
    }
    std::cout << "\n";
}

BOOST_AUTO_TEST_CASE(TestPropertyTreeJsonSave) {
    client::debug_settings debug_set("../debug_settings.xml");
    debug_set.load();
    debug_set.save();
}



BOOST_AUTO_TEST_SUITE_END()
