#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> v {2, 7, 1, 6, 2, -2, 4, 0};
int const target = 2;

TEST_CASE("Manual count") {
    int twos = 0;
    for(std::size_t i=0; i<v.size(); ++i) {
        if(v[i] == target) {
            ++twos;
        }
    }
    REQUIRE(twos == 2);
}

TEST_CASE("Count vector iterator") {
    int twos = std::count(v.begin(), v.end(), target);
    REQUIRE(twos == 2);
}

TEST_CASE("Count global iterator") {
    int twos = std::count(std::begin(v), std::end(v), target);
    REQUIRE(twos == 2);
}




