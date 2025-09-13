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

// sum是一个共享状态，
// 主线程会等待future::ready,直到sum计算完成
// future.get会一直阻塞等待，等待future::ready
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

GTEST_TEST(TplTests, SimpleFutureGet) {
    std::future<int> result = std::async(operation, 10);
    std::cout << "main() thread continues executing...\n";
    auto sum = result.get();
    std::cout << sum << std::endl;
}

// future只能get一次，get之后就不能再get了，
// 可以用valid来判断是否可用
GTEST_TEST(TplTests, SimpleFutureValid) {
    std::future<int> result = std::async(operation, 10);
    std::cout << "main() thread continues executing...\n";
    if(result.valid()) {
        auto sum = result.get();
        std::cout << sum << std::endl;
    }
}

// 默认看上去std::async是异步执行的，手动指定std::launch::async试试
GTEST_TEST(TplTests, SimpleFutureManualLaunchAsync) {
    std::future<int> result = std::async(std::launch::async, operation, 10);
    std::cout << "main() thread continues executing...\n";
    if(result.valid()) {
        auto sum = result.get();
        std::cout << sum << std::endl;
    }
}


// 异步执行，1秒钟之后输出main() thread executing
GTEST_TEST(TplTests, SimpleFutureAsyncSleep) {
    using namespace std::chrono_literals;
    std::future<int> result = std::async(std::launch::async, operation, 10);
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues executing...\n";
    if(result.valid()) {
        auto sum = result.get();
        std::cout << sum << std::endl;
    }
}

// 指定launch policy为deferred之后，任务会同步执行
// 先sleep 1秒，然后输出main() thread ...
// 然后遇到future::get才开始执行
GTEST_TEST(TplTests, AsyncLaunchDeferred) {
    using namespace std::chrono_literals;
    std::future<int> result = std::async(std::launch::deferred, operation, 10);
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues executing...\n";
    if(result.valid()) {
        auto sum = result.get();
        std::cout << sum << std::endl;
    }
}








