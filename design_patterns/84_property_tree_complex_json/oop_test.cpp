#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "property_tree_json.h"
#include <utility>
#include <memory>
#include <cstring>

#define BOOST_TEST_MODULE PropertyTreeJson
#include "test.hpp"

// 将操作系统的LANG 设置为zh_CN.UTF-8就可以
BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestPropertyTreeJsonLoad) {
    client::track_infos t_infos("./turning_indexes_tracks.json");
    t_infos.load();
    // for(auto const& track: t_infos.m_tracks) {
    //     std::cout << track << "\n";
    // }
    std::cout << "\n";
}

BOOST_AUTO_TEST_CASE(TestPropertyTreeJsonSave) {
    client::track_infos t_infos("./turning_indexes_tracks.json");
    t_infos.load();
    t_infos.save();
}


BOOST_AUTO_TEST_SUITE_END()
