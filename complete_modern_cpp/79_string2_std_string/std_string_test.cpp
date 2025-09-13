#include <iostream>
#include <string>
#include "gtest/gtest.h"

GTEST_TEST(StdStringTests, TestAssignment) {
    std::string s = "hello";
    ASSERT_EQ(s, "hello");
    s = "hello";
    ASSERT_EQ(s, "hello");
    s[0] = 'W';
    ASSERT_EQ(s, "Wello");
    char ch = s[0];
    ASSERT_EQ(ch, 'W');
}


GTEST_TEST(StdStringTests, TestCin) {
    std::string s;
    std::cout << "Please input the current string: ";
    std::getline(std::cin, s);
    ASSERT_TRUE(s.length() >=0 );
    std::cout << "string s: " <<  s << std::endl;
    std::cout << "Length of string s: " << s.length() << std::endl;
}

GTEST_TEST(StdStringTests, TestConcate) {
    std::string s1{"Hello"};
    std::string s2{"World"};
    std::string s = s1 + s2;
    ASSERT_EQ(s, "HelloWorld");
}

GTEST_TEST(StdStringTests, TestInsert) {
    std::string s1{"Hello"};
    std::string s2{"World"};
    std::string s;
    s += s1;
    s.insert(5, "World");
    ASSERT_EQ(s, "HelloWorld");
}

GTEST_TEST(StdStringTests, TestNE) {
    std::string s1{"Hello"};
    std::string s2{"World"};

    ASSERT_NE(s1, s2);
}

GTEST_TEST(StdStringTests, TestErase) {
    std::string s{"Hello,World"}, s1=s, s2=s;
    s.erase();
    ASSERT_EQ(s, "");
    s1.clear();
    ASSERT_EQ(s1, "");
    s2.erase(5, 1);
    std::cout << s2 << std::endl; 
    ASSERT_EQ(s2, "HelloWorld");
}

GTEST_TEST(StdStringTests, TestFind) {
    std::string s{"Hello, World"};
    auto pos = s.find("World", 0);
    ASSERT_TRUE(pos!= std::string::npos);
    std::cout << "World position: " << pos << std::endl;
}

std::string combine(std::string const& first, std::string const& last) {
    std::string full_name {first + last};
    return full_name;
}

GTEST_TEST(StdStringTests, TestCombine) {
    auto full_name = combine("Fredric", "Zhu");
    ASSERT_EQ(full_name, "FredricZhu");
}

GTEST_TEST(StdStringTests, TestStrLiteral) {
    using namespace std::string_literals;
    auto full_name = "Fredric Zhu"s;
    ASSERT_EQ(full_name, "Fredric Zhu");
    ASSERT_EQ(typeid(full_name), typeid(std::string)); 
}

