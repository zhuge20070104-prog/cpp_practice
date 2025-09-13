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

enum class ErrorCode {
    COPY_FAIL = -1,
    COPY_SUCCESS = 0
};

ErrorCode copy_file(std::string const& src_path, std::string const& dst_path) {
    std::ifstream source {src_path};
    if(!source) {
        LOG(std::cout, "Source file not found")
        return ErrorCode::COPY_FAIL;
    }
    std::ofstream dest {dst_path};

    std::string line;
    while(std::getline(source, line)) {
        dest << line << std::endl;
    }
    source.close();
    dest.close();
    return ErrorCode::COPY_SUCCESS;
}

GTEST_TEST(FileTests, CopyFile) {
    boost::filesystem::path source{boost::filesystem::current_path().remove_leaf()};
    boost::filesystem::path dest {source};
    
    source /= "log.hpp";
    dest /=  "result.hpp";
    std::cout << source.string() << std::endl;
    std::cout << dest.string() << std::endl;
    auto result = copy_file(source.string(), dest.string());
    ASSERT_EQ(result, ErrorCode::COPY_SUCCESS);
}

