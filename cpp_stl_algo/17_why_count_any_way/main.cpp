#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <string>

std::vector<int> v {2, 7, 1, 6, 2, -2, 4, 0};

// 使用count的几种情况
// 1. Are all of these elements __ ?
// 2. Are any of these elements __ ?
// 3. Are none of these elements __ ?


// 2. 计算有多少个奇数的传统算法
TEST_CASE("Traditional calculation") {
    int odds = 0;
    for(auto const& ele: v) {
        if(ele % 2 != 0) {
            ++odds;
        }
    }
    
    bool allof, noneof, anyof;
    allof = (odds == v.size());
    noneof = (odds == 0);
    anyof = (odds > 0);

    REQUIRE(!allof);
    REQUIRE(!noneof);
    REQUIRE(anyof);
}

// 2. 计算有多少个奇数 count_if
TEST_CASE("Count if odds") {
    int odds = std::count_if(std::begin(v), std::end(v), [](auto const& ele) {
        return ele % 2 != 0; 
    });

    bool allof, noneof, anyof;
    allof = (odds == v.size());
    noneof = (odds == 0);
    anyof = (odds > 0);

    REQUIRE(!allof);
    REQUIRE(!noneof);
    REQUIRE(anyof);
}

TEST_CASE("STL algo odds") {
    bool allof, noneof, anyof;
    allof = std::all_of(std::begin(v), std::end(v), [](auto const& elem) {
        return elem % 2 != 0;
    });

    noneof = std::none_of(std::begin(v), std::end(v), [](auto const& elem) {
        return elem % 2 != 0;
    });

    anyof = std::any_of(std::begin(v), std::end(v), [](auto const& elem) {
        return elem % 2 != 0;
    });

    REQUIRE(!allof);
    REQUIRE(!noneof);
    REQUIRE(anyof);
}