#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
// File I/O
//1. C++ 通过下面的类提供FileIO
// ofstream - 向output stream中写入值
// ifstream - 从input stream中读入值
// fstream - 可同时读写流
// 2. 包含<fstream> 头文件
// 3. 所有类可同时用于binary/text I/O
// 4. 另外他们支持文件如何打开/操作的模式
// 5. is_open函数返回一个boolean 指示文件是否open

// 文件打开模式
// 1. 下面的模式能够被用于文件打开
// 2. 这些模式是std::ios_base类中的常量
// 3. 有些模式能够组合使用，例如std::ios::in | std::ios::out
// app: 每次写之前把文件指针置到最后
// binary: 以二进制模式打开
// in: 以读取的方式打开，ifstream的默认模式
// out: 以写入的方式打开，ostream的默认模式
// trunc: 打开之前删除文件内容
// ate: 打开文件之后 跳到最后
void write() {
    std::ofstream out{"data.txt"};
    out << "Hello World" << std::endl;
    out << 10 << std::endl;
    out.close();
}

// 另外一个问题是 std::istream在读取时如果中间有空格，读不出来
// 需要用到std::getline
// 如果没有空格，可以直接使用 std::istream::operator >>
void read_by_construct() {
    std::ifstream input {"data.txt"};
    std::string message;
    std::getline(input, message);
    int value{};
    input >> value;
    input.close();
    std::cout << message << ": " << value << std::endl;
}

void read_by_open() {
    std::ifstream input;
    input.open("data.txt");
    std::string message;
    std::getline(input, message);
    int value{};
    input >> value;
    input.close();
    std::cout << message << ": " << value << std::endl;
}

GTEST_TEST(FileIOTests,  OpenUsingConstruct) {
    write();
    read_by_construct();
}

GTEST_TEST(FileIOTests, OpenUsingOpenFunc) {
    write();
    read_by_open();
}

