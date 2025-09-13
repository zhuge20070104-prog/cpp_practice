#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <string>

std::vector<int> v {2, 4, 6, 6, 1, 3, -2, 0, 11, 2, 3, 2, 4, 4, 2, 4};
std::string s {"Hello I am a sentence"};
// 1. Find的使用场景
// find可以用在while循环里面
// 找到某个元素之后返回一个迭代器，
// 然后在while里面使用这个迭代器 + 1，再接着往后找
// 直到找到iterator end为止
// 就可以找完了

// Finding用法
// First element with a specific value: find()
// First element meeting a condition: find_if()
// Returns an iterator

// 整型集合Find
TEST_CASE("Find in a integer collection") {
    // Find the first zero in the collection
    auto result = std::find(std::begin(v), std::end(v), 0);
    int we_looked_for = *result;

    REQUIRE(we_looked_for == 0);
    // Find the first two after that zero
    result = std::find(result, std::end(v), 2);
    if(result != std::end(v)) {
        we_looked_for = *result;
    }
    REQUIRE(we_looked_for == 2);
}

TEST_CASE("Find in an std::string") {
    // Find the first 'a'
    auto letter = std::find(std::begin(s), std::end(s), 'a');
    char a = *letter;
    REQUIRE(a == 'a');
}

TEST_CASE("Find the first ODD & Even value") {
    auto result = std::find_if(std::begin(v), std::end(v), [](auto const& elem) {
        return elem % 2 != 0;
    });

    REQUIRE(*result == 1);
    result = std::find_if(std::begin(v), std::end(v), [](auto const& elem){
        return elem % 2 == 0;
    });
    REQUIRE(*result == 2);
}

TEST_CASE("Find all odd values") {
    std::vector<int> odd_values;
    for(auto result = std::begin(v);result != std::end(v);) {   
        result = std::find_if(result, std::end(v), [](auto const& elem) {
            return elem % 2 != 0;
        });

        if(result == std::end(v)) {
            break;
        } else {
            odd_values.push_back(*result);
            ++result;
        }
    }

    REQUIRE(odd_values == std::vector<int>{1,3,11,3});
}






