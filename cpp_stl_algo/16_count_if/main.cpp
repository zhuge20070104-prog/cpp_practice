#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <string>

std::vector<int> v {2, 7, 1, 6, 2, -2, 4, 0};

TEST_CASE("Manual count if") {
    int odds = 0;
    for(auto const& ele: v) {
        if(ele % 2 != 0) {
            ++odds;
        }
    }
    REQUIRE(odds == 2);
}

TEST_CASE("Count if vector") {
    int odds = std::count_if(std::begin(v), std::end(v), [](auto const& ele) {
        return ele % 2 != 0; 
    });

    REQUIRE(odds == 2);
}

TEST_CASE("Count if map") {
    std::map<int, int> month_lengths {{1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31},
        {6, 30}, {7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31}};
    int long_months = std::count_if(std::begin(month_lengths), std::end(month_lengths),
        [](auto const& elem) {
            return elem.second == 31;
        });
    REQUIRE(long_months == 7);
}