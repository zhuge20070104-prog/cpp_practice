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


// std::promise
// 1. 提供一种方法来存储值，或者异常
// 2. 这被称作共享状态
// 3. 这个共享状态可以稍后从其他线程里面通过future对象访问
// 4. promise/future 是一个通信通道的两端
// 5. 一个操作通过promise存储值，另一个操作通过future异步获取值
// 6. 这些操作之间有线程同步，因此，线程安全
// 7. promise对象只能使用一次

// share_state可以手动设置，也可以直接使用返回值
// promise里面保存了一个shared_state状态，当shared_state ready的时候，
// future会知道这个ready,就可以调用future::get获取这个shared_state,
// shared_state只能使用一次，使用之前必须使用valid做判断
// 可以把shared_state看做promise和future之间的一个channel

int operation(std::promise<int>&& prim) {
    using namespace std::chrono_literals;
    auto f = prim.get_future();
    std::cout << "[Task] Waiting for count\n";
    auto count = f.get();
    std::cout << "[Task] Count acquired\n";
    int sum{};
    for(int i=0; i<count; ++i) {
        sum += i;
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(300ms);
    }
    return sum;
}


int operation_ref(std::promise<int>& prim) {
    using namespace std::chrono_literals;
    auto f = prim.get_future();
    std::cout << "[Task] Waiting for count\n";
    auto count = f.get();
    std::cout << "[Task] Count acquired\n";
    int sum{};
    for(int i=0; i<count; ++i) {
        sum += i;
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(300ms);
    }
    return sum;
}

// std::promise不能拷贝，所以要用std::move或者std::ref传
// 此处也可以用prom.get_feature传递feature
GTEST_TEST(TplTests, PromisePassByStdMove) {
    using namespace std::chrono_literals;
    std::promise<int> prom;
    prom.set_value(10);
    std::future<int> result = std::async(std::launch::async, operation, std::move(prom));
    std::this_thread::sleep_for(1s);
    std::cout << "main() thread continues executing...\n";
    if(result.valid()) {
        auto sum = result.get();
        std::cout << sum << std::endl;
    }
}


// 传递std::ref
GTEST_TEST(TplTests, PromisePassByStdRef) {
    using namespace std::chrono_literals;
    std::promise<int> prom;
    std::future<int> result = std::async(std::launch::async, operation_ref, std::ref(prom));
    std::this_thread::sleep_for(1s);
    std::cout << "Setting the data in promise...\n";
    // 1秒之后设置promise
    prom.set_value(10);
    if(result.valid()) {
        auto sum = result.get();
        std::cout << sum << std::endl;
    }
}

