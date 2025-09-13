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


// 线程之间传递exception需要用exception pointer，不能直接用exception对象

// 子线程传给主线程，std::thread，需要用std::promise带出去 prom_out
void operation_thread(std::promise<int>& prom_in, std::promise<int>& prom_out) {
    using namespace std::chrono_literals;
    auto fut = prom_in.get_future();
    std::cout << "[Task] Waiting for count\n";
    int count = fut.get();
    std::cout << "[Task] Count acquired\n";
    try {
        int sum{};
        for(int i=0; i<count; ++i) {
            sum+=i;
            std::cout << ".";
            std::cout.flush();
            std::this_thread::sleep_for(300ms);
        }
        throw std::runtime_error("Calculation exception");
        prom_out.set_value(sum);
    } catch(...) {
        prom_out.set_exception(std::current_exception());
    }
}


// 子线程传给主线程, std::async, 直接throw
int operation_async(std::promise<int>& prom) {
    using namespace std::chrono_literals;
    auto fut = prom.get_future();
    std::cout << "[Task] Waiting for count\n";
    int count = fut.get();
    std::cout << "[Task] Count acquired\n";

    int sum{};
    for(int i=0; i<count; ++i) {
        sum+=i;
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(300ms);
    }
    throw std::runtime_error("Calculation exception in Operation Async");
    return sum;
}

// Exception 被promise传递到了子线程，调用fut::get的时候，因为有exception,
// exception会被跑出来，
// 这样子线程可以catch到这个exception
int operation_except(std::promise<int>& prom) {
    using namespace std::chrono_literals;
    try {
        auto fut = prom.get_future();
        std::cout << "[Task] Waiting for count\n";
        int count = fut.get();
        std::cout << "[Task] Count acquired\n";
        int sum{};
        for(int i=0; i<count; ++i) {
            sum+=i;
            std::cout << ".";
            std::cout.flush();
            std::this_thread::sleep_for(300ms);
        }
        return sum;
     } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }   
}

GTEST_TEST(TplTests, ExceptionAcrossThreads) {
    using namespace std::chrono_literals;
    std::promise<int> prom_in;
    std::promise<int> prom_out;
    auto fut = prom_out.get_future();
    std::thread th_sum(operation_thread, std::ref(prom_in), std::ref(prom_out));
    std::this_thread::sleep_for(1s);
    std::cout << "Setting the data in promise...\n";
    // 1秒之后设置promise
    prom_in.set_value(10);
    
    try {
        auto sum = fut.get();
        std::cout << "Sum: " << sum << std::endl;
    }catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    th_sum.join();
}


GTEST_TEST(TplTests, ExceptionAsync) {
    using namespace std::chrono_literals;
    std::promise<int> prom;
    auto fut = std::async(std::launch::async, operation_async, std::ref(prom));
    std::this_thread::sleep_for(1s);
    std::cout << "Setting the data in promise...\n";
    // 1秒之后设置promise
    prom.set_value(10);

    try {
        auto sum = fut.get();
        std::cout << sum << std::endl;
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}


// 这是在主线程抛异常，异常传递给子线程
// 也可以直接在子线程抛异常，把异常传递给主线程，
// 这样子线程里面的异常直接抛出就可以，runtime会对exception做exception_ptr的包装，然后把exception pointer抛出来
// 主线程在fut::get的时候会捕获到这个异常
GTEST_TEST(TplTests, ExceptionInMainThread) {
    using namespace std::chrono_literals;
    std::promise<int> prom;
    auto fut = std::async(std::launch::async, operation_except, std::ref(prom));
    std::this_thread::sleep_for(1s);
    std::cout << "Setting the data in promise...\n";
    // 1秒之后设置promise
     try {
        throw std::runtime_error("Data not available");
        prom.set_value(10);
        auto sum = fut.get();
        std::cout << sum << std::endl;
    } catch(...) {
        prom.set_exception(std::current_exception());
    }
}


