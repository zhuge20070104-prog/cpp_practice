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

// 文件读取，错误处理
// 文件流状态的各个标志位，以及各个函数
// 1. good bit 含义：no error  函数: bool good()
// 2. bad bit 含义: 不可恢复的stream error 函数： bool bad()
// 3. fail bit 含义: io operation 失败 函数: bool fail()  [operator!]
// 4. eof bit 含义: 输入的时候遇到end of file  函数: bool eof()

void write() {
    std::ofstream out {"data.txt"};
    out << "Hello world" << std::endl;
    out << 10 << std::endl;
    out.close();
}

void read_is_open() {
    std::ifstream input {"dat.txt"};
    if(!input.is_open()) {
        std::cout << "Could not open the file" << std::endl;
        return;
    }

    std::string message;
    std::getline(input, message);
    int value {};
    input >> value;
    input.close();
    std::cout << message << ": " << value << std::endl;
}

void read_good() {
    std::ifstream input {"data.txt"};
    if(!input.is_open()) {
        std::cout << "Could not open the file" << std::endl;
        return;
    }

    std::string message;
    std::getline(input, message);
    int value {};
    input >> value;
    // 都读完了以后测试当前流的状态是否完好，是否有错误出现
    // 发现所有I/O operations都是成功的
    if(input.good()) {
        std::cout << "I/O operations are successful" << std::endl;
    } else {
        std::cout << "Some I/O operations failed" << std::endl; 
     }
    input.close();
    std::cout << message << ": " << value << std::endl;
}

// input.fail也可以用来检查文件是否打开失败
void read_fail() {
    std::ifstream input {"dat.txt"};
    if(input.fail()) {
        std::cout << "Could not open the file" << std::endl;
        return;
    }

    std::string message;
    std::getline(input, message);
    int value {};
    input >> value;
    // 都读完了以后测试当前流的状态是否完好，是否有错误出现
    // 发现所有I/O operations都是成功的
    if(input.good()) {
        std::cout << "I/O operations are successful" << std::endl;
    } else {
        std::cout << "Some I/O operations failed" << std::endl; 
     }
    input.close();
    std::cout << message << ": " << value << std::endl;
}

// 两次读取同一个值，没读到，会产生error，导致input.fail()为true
void read_twice_error() {
    std::ifstream input {"data.txt"};
    if(input.fail()) {
        std::cout << "Could not open the file" << std::endl;
        return;
    }

    std::string message;
    std::getline(input, message);
    int value {};
    input >> value;
    input >> value;

    if(input.fail()) {
        std::cout << "Could not read value again" << std::endl;
    }
    // 都读完了以后测试当前流的状态是否完好，是否有错误出现
    if(input.good()) {
        std::cout << "I/O operations are successful" << std::endl;
    } else {
        std::cout << "Some I/O operations failed" << std::endl; 
     }
    input.close();
    std::cout << message << ": " << value << std::endl;
}

void read_set_state() {
    std::ifstream input {"data.txt"};
    if(input.fail()) {
        std::cout << "Could not open the file" << std::endl;
        return;
    }

    std::string message;
    std::getline(input, message);
    int value {};
    input >> value;
    input >> value;

    if(input.eof()) {
        std::cout << "End of file encountered" << std::endl;
    }
    // 都读完了以后测试当前流的状态是否完好，是否有错误出现
    if(input.good()) {
        std::cout << "I/O operations are successful" << std::endl;
    } else {
        std::cout << "Some I/O operations failed" << std::endl; 
     }
     // clear 函数清空所有标志位
     // setstate函数设置单个标志位
     // std::ios::failbit和其他标志位是 | 关系
     input.setstate(std::ios::failbit);
     input.clear();
    input.close();
    std::cout << message << ": " << value << std::endl;
}


GTEST_TEST(FileTests, ReadIsOpen) {
    write();
    read_is_open();
}

GTEST_TEST(FileTests, ReadGood) {
    write();
    read_good();
}

GTEST_TEST(FileTests, ReadFail) {
    write();
    read_fail();
}

GTEST_TEST(FileTests, ReadTwiceError) {
    write();
    read_twice_error();
}

GTEST_TEST(FileTests, ReadSetState) {
    write();
    read_set_state();
}