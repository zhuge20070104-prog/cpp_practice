#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include "gtest/gtest.h"

class Distance {
    long double m_killometers;
public:
    Distance(long double km): m_killometers(km) {
    }
    
    long double get_km() const {
        return m_killometers;
    }

    void set_km(long double val) {
        m_killometers = val;
    }
};

Distance operator "" _mi(long double val) {
    return Distance {val/1000};
} 

Distance operator "" _metres(long double val) {
    return Distance {val/1000};
}

GTEST_TEST(StdStringTests, TestUDFLiterals) {
    // 注意事项: 1. 自定义的string_literals必须以_开头
    //  2.只有以下类型支持用户自定义literals, unsigned long long, long double, char const*, char
    //  3. Literal操作符函数不能是成员函数
    Distance dis{32.0_mi};
    Distance dis2{7123.0_metres};

    std::cout << "dis: " << dis.get_km() << " km" << std::endl;
    std::cout << "dis2: " << dis2.get_km() << " km" << std::endl;
    ASSERT_TRUE(fabs(dis.get_km() - 0.032) < 0.001);
    ASSERT_TRUE(fabs(dis2.get_km() - 7.123) < 0.001);
}
