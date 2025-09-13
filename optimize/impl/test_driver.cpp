#include "test_driver.h"
#include "priority_thread.h"

#include <iostream>
#include <cstring>

// 运行多少 千 次
// 默认1*1000
// 参数通过 ./xxx_test  -x2 传入
void test_driver(test_func* flist, int argc, char** argv) {
    unsigned long multiplier = 1;
    if(argc > 1) {
        // 第一个参数的前面两个是 -x，例如 ./xxxx_test -x3
        if(strncmp(argv[1], "-x", 2) == 0) {
            // 从 -x后面的数字开始，转换成ulong
            multiplier = strtoul(argv[1]+2, nullptr, 10);
        }
    } 

    // 测试函数列表为空，多个函数
    if(flist == nullptr) {  
        std::cout << "No test function" << std::endl;
    } else {
        std::cout << "multiplier set to " << multiplier << std::endl;
        // 进程拉到前台
        PriorityThread p;
        // 逐个执行flist中的函数
        for(unsigned f=0; flist[f]!=0; ++f) {
            if(flist[f] == nullptr) {
                continue;
            }

            // 执行测试合集， 合集的测试号为1， 0返回所有测试个数，2-end是单个测试
            if(flist[f](1, multiplier) == 1) {
                std::cout << "All tests pass" << std::endl;
            } else {
                std::cout << "Tests failed" << std::endl;
            }

            for(int i=2, e=flist[f](0, multiplier); i<=e; ++i) {
                if(flist[f](i, multiplier) != 1) {
                    std::cout << "test " << i << " failed" << std::endl;
                }
            }
        }
    }
}

void test_driver(test_func f, int argc, char** argv) {
    unsigned long multiplier = 1;
    if(argc > 1) {
        if(strncmp(argv[1], "-x", 2) == 0) {
            multiplier = strtoul(argv[1]+2, nullptr, 10);
        }
    }

    if(f == nullptr) {
        std::cout << "no test function" << std::endl;
    } else {
        std::cout << "multiplier set to: " << multiplier << std::endl;

        PriorityThread p;
        if(f(1, multiplier) == 1) {
            std::cout << "all tests pass" << std::endl;
        } else {
            std::cout << "tests failed" << std::endl;
        }

        for(int i=2, e=f(0, multiplier); i<=e; ++i) {
            if(f(i, multiplier) != 1) {
                std::cout << "test " << i << " failed" << std::endl;
            }
        }
    }


}