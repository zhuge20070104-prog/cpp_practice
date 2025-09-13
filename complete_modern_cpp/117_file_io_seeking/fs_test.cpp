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

void write_char() {
    std::ofstream out {"test.txt"};
    if(!out) {
        LOG(std::cout, "Could not open file for writing")
        return;
    }

    std::string message {"C++ was invented by Bjarne"};
    for(char const& ch: message) {
        out.put(ch);
    }
}

void write_char_seek_p() {
    std::ofstream out {"test.txt"};

    if(!out) {
        LOG(std::cout, "Could not open file for writing")
        return;
    }

    std::string message{"C++ was invented by Bjarne"};
    for(char ch: message) {
        out.put(ch);
    }

    // 第5个位置写入一个#
    out.seekp(5);
    out.put('#');
}



void read_char() {
    std::ifstream input {"test.txt"};
    if(!input) {
        LOG(std::cout, "Source file not found")
        return;
    }
    char ch {};
    while(input.get(ch)) {
        std::cout << ch;
    }
}


// tell_g 获取文件的当前位置, 获取失败的话会返回-1
void read_char_tell_g() {
    std::ifstream input {"test.txt"};
    if(!input) {
        LOG(std::cout, "Source file not found")
        return;
    }
    char ch {};
    LOG(std::cout, "Current position is: ", input.tellg())
    while(input.get(ch)) {
        std::cout << ch;
    }
}

// tellg, tell get pointer， 获取get pointer读取的位置
// tellp, tell put pointer, 获取写入的put pointer所在位置
// seekg, 改变读取的get pointer所在位置
// seekp, 改变写入的put pointer所在位置
void read_char_seek_and_tell_g() {
    std::ifstream input {"test.txt"};
    if(!input) {
        LOG(std::cout, "Source file not found")
        return;
    }
    char ch {};
    input.seekg(5);
    LOG(std::cout, "Current position is: ", input.tellg())
    while(input.get(ch)) {
        std::cout << ch;
    }
}

// seek_g 还有一个重载，第二个参数可以支持三个值
// std::ios::begin 相对开始位置
// std::ios::cur 相对当前位置
// std::ios::end 相对结束位置
void read_char_seek_end_and_tell_g() {
    std::ifstream input {"test.txt"};
    if(!input) {
        std::cout << "Source file not found" << std::endl;
        return;
    }

    // 从后面数倒数第5个
    input.seekg(-5, std::ios::end);
    std::cout << "Current position is: " << input.tellg() << std::endl;
    char ch {};
    while(input.get(ch)) {
        std::cout << ch;
    }
}

// fstream 默认打开文件方式可读可写，但是他在没有文件时，不创建文件
void using_fstream() {
    std::fstream stream {"file.txt"};
    if(!stream) {
        std::cout << "File doesn't exist, creating one..." << std::endl;
        // 先用ofstream创建文件，再用fstream打开
        std::ofstream out {"file.txt"};
        out.close();
        stream.open("file.txt");
    }

    stream << "Hello world" << std::endl;
    // 因为他是一个可读可写的文件流，里面有get pointer和put pointer
    //  写完之后,get 和 put pointer都到了eof
    // 所以要先seekg到0，才能读
    stream.seekg(0);
    std::string line;
    std::getline(stream, line);
    std::cout << line << std::endl;
}

GTEST_TEST(FileTests, WriteAndRead) {
    write_char();
    read_char();
}

GTEST_TEST(FileTests, WriteAndReadTellg) {
    write_char();
    read_char_tell_g();
}

GTEST_TEST(FileTests, WriteAndReadSeekTellg) {
    write_char();
    read_char_seek_and_tell_g();
}

GTEST_TEST(FileTests, WriteAndReadCharSendEndAndTellG) {
    write_char();
    read_char_seek_end_and_tell_g();
}

GTEST_TEST(FileTests, SeekPAndWriteChar) {
    write_char_seek_p();
    read_char();
}

GTEST_TEST(FileTests, UsingFStream) {
    using_fstream();
}

