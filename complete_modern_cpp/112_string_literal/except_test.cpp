#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include "log.hpp"

//  Raw string出现特殊字符时，会出现conruppted的情况
GTEST_TEST(StringLiteralTest,  RawStringCunruptted) {
    std::string file_name {"c:\temp\newfile.txt"};
    std::cout << "Conruptted file name: " << file_name << std::endl;
    ASSERT_EQ(file_name, "c:\temp\newfile.txt");
}

// 加转义字符可以处理这种情况
GTEST_TEST(StringLiteralTest, EscapedCharacter) {
    std::string file_name {"c:\\temp\\newfile.txt"};
    std::cout << "Escaped file name: " << file_name << std::endl;
    ASSERT_EQ(file_name, "c:\\temp\\newfile.txt");
}

// 使用 R"()"  组成的raw string也可以处理
GTEST_TEST(StringLiteralTest, RawStringR) {
    std::string file_name {R"(c:\temp\newfile.txt)"};
    std::cout << file_name << std::endl;
    ASSERT_EQ(file_name, R"(c:\temp\newfile.txt)");
}

// 当raw string里面有()时，就不能直接用()了
// 需要自定义分割符，例如下面例子的分割符就是  R"MSG()MSG"
GTEST_TEST(StringLiteralTest, RawStringFail) {
    std::string message {R"MSG(C++ introduced filesystem API"(In C++11)")MSG"};
    std::cout << message << std::endl;
    ASSERT_EQ(message, R"MSG(C++ introduced filesystem API"(In C++11)")MSG");
}