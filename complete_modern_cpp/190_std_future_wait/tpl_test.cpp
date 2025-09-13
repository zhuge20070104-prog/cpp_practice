#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <chrono>
#include <fstream>
#include <list>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <future>
#include <pthread.h>
#include <boost/type_index.hpp>


int operation(int count) {
    using namespace std::chrono_literals;
    int sum{};
    for(int i=0; i<count; ++i) {
        sum += i;
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(300ms);
    }
    return sum;
}

// std::future的简单wait方法，只等待，不接受返回值，如果要接受返回值，仍然要调用get方法
// wait 之前要先检查future是否valid
// wait 等待完事儿，就直接get了
GTEST_TEST(TplTests, AsyncLaunchDeferred) {
    using namespace std::chrono_literals;
    std::future<int> result = std::async(std::launch::deferred, operation, 10);
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues executing...\n";
    if(result.valid()) {
        std::cout << "Before wait..." << std::endl;
        result.wait();
        std::cout << "After wait..." << std::endl;
        auto sum = result.get();
        std::cout << sum << std::endl;
    }
}

// wait_for一般用于循环检查task是否ready
// 如果task是deferred，就不会等待，直接跳过wait_for，因为deferred是同步执行的
GTEST_TEST(TplTests, WaitForDemo) {
    using namespace std::chrono_literals;
    std::future<int> result = std::async(std::launch::async, operation, 10);
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues execution...\n";

    std::future_status status;
    do {
        if(!result.valid()) break;

        status = result.wait_for(1s);
        switch(status) {
            case std::future_status::deferred:
                std::cout << "Task is Synchronous\n";
                break;
            case std::future_status::ready:
                std::cout << "Result is ready\n";
                break;
            case std::future_status::timeout:
                std::cout << "Task is still running\n";
                break;
        }   
    } while(status != std::future_status::ready);
   
   std::cout << "Before get..." << std::endl;
   auto sum = result.get();
   std::cout << "After get..." << std::endl;
   std::cout << sum << std::endl; 
}


// wait_until和wait_for的区别就是它接受一个time_point
GTEST_TEST(TplTests, WaitUtilDemo) {
      using namespace std::chrono_literals;
    std::future<int> result = std::async(std::launch::async, operation, 10);
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues execution...\n";

    std::future_status status;
    do {
        if(!result.valid()) break;
        auto time_point = std::chrono::system_clock::now();
        time_point += 1s;
        status = result.wait_until(time_point);
        switch(status) {
            case std::future_status::deferred:
                std::cout << "Task is Synchronous\n";
                break;
            case std::future_status::ready:
                std::cout << "Result is ready\n";
                break;
            case std::future_status::timeout:
                std::cout << "Task is still running\n";
                break;
        }   
    } while(status != std::future_status::ready);
   
   std::cout << "Before get..." << std::endl;
   auto sum = result.get();
   std::cout << "After get..." << std::endl;
   std::cout << sum << std::endl; 
}





