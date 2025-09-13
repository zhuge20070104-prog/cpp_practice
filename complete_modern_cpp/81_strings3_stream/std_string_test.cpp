#include <iostream>
#include <string>
#include <sstream>
#include "gtest/gtest.h"


GTEST_TEST(StdStringTests, TestBasicUsage) {
    std::stringstream ss;
    int a{5}, b{6};
    int sum = a + b;
    ss << "Sum of " << a << " & " << b <<  " is: " << sum << std::endl;
    ASSERT_EQ(ss.str(), "Sum of 5 & 6 is: 11\n");
    // Clear the current stringstream
    ss.str("");
    ASSERT_EQ(ss.str(), "");
}

GTEST_TEST(StdStringTests, TestInt2Str) {
    int sum{11};
    std::stringstream ss;
    ss << sum;
    ASSERT_EQ(ss.str(), "11");
    ASSERT_EQ(std::to_string(sum), "11");
}

GTEST_TEST(StdStringTests, TestStr2Int) {
    std::string data{"12 89 21"};
    std::vector<int> vec_data;
    int a;
    std::stringstream ss(data);
    while(ss >> a) {
        vec_data.push_back(a);
    }

   std::vector<int> expect_data{12, 89, 21};
   for(std::size_t i=0; i<vec_data.size();  ++i) {
    ASSERT_EQ(vec_data[i], expect_data[i]);
   }
}

GTEST_TEST(StdStringTests, TestStr2Int2) {
    std::string s = "54";
    ASSERT_EQ(std::stoi(s), 54);
}



