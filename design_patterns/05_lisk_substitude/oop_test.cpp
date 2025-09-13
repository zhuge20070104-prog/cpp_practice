#include <iostream>
#include <string>
#include <sstream>
#include "gtest/gtest.h"
#include "rect.hpp"
#include "log.hpp"



GTEST_TEST(OopTest, TestLiskSubstitude) {
    auto rect = RectFactory::create_rect(3, 4);
    int area_r = process(&rect);
    LOG(std::cout, "Rect Area: ", std::to_string(area_r).c_str());
    ASSERT_EQ(area_r, 30);

    auto square = RectFactory::create_square(5);
    int area_s = process(&square);
    LOG(std::cout, "Square area: ", std::to_string(area_s).c_str());
    ASSERT_EQ(area_s, 100);
}

