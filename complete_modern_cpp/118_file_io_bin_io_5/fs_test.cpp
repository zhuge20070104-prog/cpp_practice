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



GTEST_TEST(FileTests, WriteAndReadBin) {
    std::ofstream text_stream {"data"};
    text_stream << 12345678;

    std::ofstream bin_stream {"binary", std::ios::binary | std::ios::out};
    int num {12345678};
    bin_stream.write((const char*)&num, sizeof(num));
    num = 0;
    // 要先关闭写入的文件，才能重新打开做读取
    // 因为ofstream和ifstream代表写入和读取两个操作的文件句柄
    // 不能两个句柄同时操作一个文件
    bin_stream.close();
    std::ifstream input {"binary", std::ios::binary | std::ios::in};
    input.read((char*)&num, sizeof(num));
    LOG(std::cout, "num: ", num)
    ASSERT_EQ(num, 12345678);
}


struct Record {
    int id;
    char name[10];
};

void write_record(Record* p) {
    std::ofstream bin_stream {"records", std::ios::binary | std::ios::out};
    bin_stream.write((char const*)p, sizeof(Record));
}

Record get_record() {
    std::ifstream input {"records", std::ios::binary | std::ios::in};
    Record r;
    input.read((char*)&r, sizeof(Record));
    return r;
}

// 如果要写入多个二进制结构进入文件，需要先写入结构的个数，然后开始写入结构
// 读的时候先读个数，因为二进制文件是没有eof标志符的
GTEST_TEST(FileTests, WriteAndReadRecords) {
    Record r;
    r.id = 1001;
    std::strcpy(r.name, "Fred");
    write_record(&r);
    auto r2 = get_record();
    std::cout << r2.id << ": " << r2.name << std::endl;
    ASSERT_EQ(r2.id,  1001);
    ASSERT_EQ(std::string(r2.name), "Fred");
}