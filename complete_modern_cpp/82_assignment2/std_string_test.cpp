#include <iostream>
#include <string>
#include <cstring>
#include "gtest/gtest.h"


enum class Case {
    SENSITIVE,
    INSENSITIVE
};

std::string to_lower(std::string const& str) {
    std::string res;
    res.resize(str.size());
    for(std::size_t i=0; i<str.size(); ++i) {
        res[i] = tolower(str[i]);
    }
    return res;
}

std::size_t Find(std::string const& source,
    std::string const& search_string,
    Case search_case=Case::INSENSITIVE,
    std::size_t offset=0) {
    auto temp_source = source;
    auto temp_search = search_string;
    if(search_case == Case::INSENSITIVE) {
        temp_source = to_lower(source);
        temp_search = to_lower(search_string);
    } 
    return temp_source.find(temp_search, offset);
}

GTEST_TEST(StdStringTests, TestFind) {
    std::string s{"Hello World"};
    std::string search_str{"world"};
    auto pos = Find(s, search_str, Case::SENSITIVE);
    ASSERT_EQ(pos, std::string::npos);
    
    pos = Find(s, search_str, Case::INSENSITIVE);
    ASSERT_EQ(pos, 6);
}
