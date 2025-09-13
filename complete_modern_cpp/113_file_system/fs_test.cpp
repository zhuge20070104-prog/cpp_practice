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


// 获取path中的文件名
GTEST_TEST(FileSystemTests,  PrintFileName) {
    boost::filesystem::path p {"/home/fredric/code.txt"};
    if(p.has_filename()) {
        LOG(std::cout, "File Name: ", p.filename().string())
        ASSERT_EQ(p.filename().string(), "code.txt");
    }
}

// 打印所有子path
// 注意 / 根目录也是一个path
GTEST_TEST(FileSystemTests, PrintPaths) {
    boost::filesystem::path p{"/home/fredric/code.txt"};
    std::vector<std::string> sub_paths;
    for(auto const& x: p) {
        sub_paths.push_back(x.string());
        LOG(std::cout, "Sub path: ", x.string())
    }
    ASSERT_LIST_EQ(sub_paths.begin(), sub_paths.end(), {"/", "home", "fredric", "code.txt"});
}

// 列出当前目录下所有文件，不递归，递归要自己写
GTEST_TEST(FileSystemTests, DirectoryIt) {
    boost::filesystem::path p{"/home/fredric/vpn"};
    boost::filesystem::directory_iterator  begin{p};
    boost::filesystem::directory_iterator end{};
    while(begin != end) {
        std::cout << *begin << std::endl;
        ++begin;
    }
}
