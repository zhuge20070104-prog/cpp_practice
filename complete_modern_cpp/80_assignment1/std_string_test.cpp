#include <iostream>
#include <string>
#include <cstring>
#include "gtest/gtest.h"

std::string to_upper(std::string const& str) {
    std::string res;
    res.resize(str.size());
    for(std::size_t i=0; i<str.size(); ++i) {
        res[i] = toupper(str[i]);
    }
    return res;
}

std::string to_lower(std::string const& str) {
    std::string res;
    res.resize(str.size());
    for(std::size_t i=0; i<str.size(); ++i) {
        res[i] = tolower(str[i]);
    }
    return res;
}

GTEST_TEST(StdStringTests, TestToUpper) {
    std::string lower_str{"green tea"};
    auto upper_str = to_upper(lower_str);
    ASSERT_EQ(upper_str, "GREEN TEA");
}

GTEST_TEST(StdStringTests, TestToLower) {
    std::string upper_str{"GREEN TEA"};
    auto lower_str = to_lower(upper_str);
    ASSERT_EQ(lower_str, "green tea");
}



