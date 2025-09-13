#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <string>

std::vector<int> v {2, 4, 6, 6, 1, 3, -2, 0, 11, 2, 3, 2, 4, 4, 2, 4};
std::string s {"Hello I am a sentence"};

// 1. Find的变体
// find_if_not
// find_first_of
// search
// find_end
// search_n
// adjacent_find


TEST_CASE("Find if find the first odd number") {
    auto result = std::find_if(std::begin(v), std::end(v), [](auto const& elem) {
        return elem % 2 != 0;
    });

    int we_looked_for = *result;
    REQUIRE(we_looked_for == 1);
    REQUIRE(result == std::begin(v) + 4);
}


TEST_CASE("Find if not find the first even number") {
    // Find the first even number
    auto result = std::find_if_not(std::begin(v), std::end(v), [](auto const& elem) {
        return elem % 2 != 0;
    });

    int we_looked_for = *result;
    REQUIRE(we_looked_for == 2);
    REQUIRE(result == std::begin(v));
}

TEST_CASE("Find first of find the first intersect element") {
    // find_first_of
    // 这将会找到 v里面的第一个元素2，
    // 因为primes里面有个2
    std::vector<int> primes {1, 2, 3, 5, 7, 11, 13};
    auto result = std::find_first_of(std::begin(v), std::end(v), std::begin(primes), 
        std::end(primes));
    int we_looked_for = *result;
    REQUIRE(we_looked_for == 2);
    REQUIRE(result == std::begin(v));
}

TEST_CASE("Search search for 2 and 4") {
    std::vector<int> subsequence {2, 4};
    auto result = std::search(std::begin(v), std::end(v), std::begin(subsequence), 
        std::end(subsequence));
    int we_looked_for = *result;
    REQUIRE(we_looked_for == 2);
    we_looked_for = *++result;
    REQUIRE(we_looked_for == 4);
    we_looked_for = *++result;
    REQUIRE(we_looked_for == 6);
}

TEST_CASE("Search for am in string") {
    std::string am = "am";
    auto letter = std::search(std::begin(s), std::end(s), std::begin(am), std::end(am));
    REQUIRE(*letter == 'a');
    REQUIRE(*++letter == 'm');
}

TEST_CASE("Find end search the last 2 and 4") {
    std::vector<int> subsequence {2, 4};
    auto result = std::find_end(std::begin(v), std::end(v), std::begin(subsequence),
        std::end(subsequence));
    
    REQUIRE(*result == 2);
    REQUIRE(*++result == 4);
    REQUIRE(++result == std::end(v));
}

TEST_CASE("Search n search for two continuous 4") {
    auto result = std::search_n(std::begin(v), std::end(v), 2, 4);
    REQUIRE(*result == 4);
    REQUIRE(*++result == 4);
    REQUIRE(*++result == 2);
}

TEST_CASE("Adjacent find find two continuous elements") {
    auto result = std::adjacent_find(std::begin(v), std::end(v));
    REQUIRE(*result == 6);
    REQUIRE(*++result == 6);
    REQUIRE(*++result == 1);
}