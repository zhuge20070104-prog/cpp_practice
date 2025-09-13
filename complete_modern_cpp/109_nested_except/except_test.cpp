#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <memory>
#include <random>
#include "gtest/gtest.h"
#include "log.hpp"

class Test {
public:
    Test() {
        std::cout << "Test::Test() Acquiring Resources" << std::endl;
    }

    ~Test() {
        std::cout << "Test::~Test() Releasing Resources" << std::endl;
    }
};

// 注意exception rethrow的用法
void process_records_good(int count) {
    std::unique_ptr<Test> t(new Test);
    if(count < 10) {
        throw std::out_of_range("Count should be greater than 10");
    }

    std::vector<int> arr;
    arr.reserve(count); // reserver 失败会 抛出std::bad_alloc异常
    for(int i=0; i<count; ++i) {
        arr.push_back(i);
    }

    std::default_random_engine eng;
    std::bernoulli_distribution dist;
    int errors{};
    for(int i=0; i<count; ++i) {
        try {
            std::cout << "Processing record #: " << i << std::endl;
            // 伯努利分布是一个0，1分布，伯努利分布输出0时， throw exception
            if(!dist(eng)) {
                ++ errors;
                throw std::runtime_error("Could not process the record");
            }
        }catch(std::runtime_error& ex) {
            LOG(std::cout, "[ERROR: ", ex.what(), "]")
            if(errors > 4) {
                std::runtime_error err("Two many errors, abanding operation");
                ex = err; // 引用捕获，直接修改原值，把已经捕获的ex进行修改，然后re-throw出去
                throw;
            }
        }
    }
}



GTEST_TEST(ExceptTest, ProcessRecordsGoodTest) {
    try {
        process_records_good(100);
    }catch (std::exception& ex) {
        LOG(std::cout, ex.what())
    }
}




