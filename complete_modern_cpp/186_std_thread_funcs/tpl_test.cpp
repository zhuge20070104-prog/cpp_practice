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

#define ERROR_CHECK(error_code, success_stmt, error_stmt) \
	if(error_code == 0) \
		std::cout << success_stmt << std::endl; \
	else \
		std::cout << error_stmt << ", error_code: " << error_code << std::endl; \

void process() {
}

void process2() {
	// sleep for 可以制造delay
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void process3() {
	std::cout << "线程ID: " << std::this_thread::get_id() << std::endl;
}


// id是一个类，但是该类重载了插入操作符，
// 所以我们可以在控制台打印他
GTEST_TEST(TplTests, StdThreadGetId) {
	std::thread t1(process);
	auto id = t1.get_id();
	std::cout << id << std::endl;
	t1.join();
}

// native_handle是一个跟平台相关的线程对象，在Windows平台上是HANDLE,
// 在Linux平台上是pthread_t, unsigned long类型的数值
GTEST_TEST(TplTests, StdThreadNativeHandle) {
	std::thread t1(process);
	auto handle = t1.native_handle();
	std::cout << "Native Handle Type: " << boost::typeindex::type_id_runtime(handle).pretty_name() << std::endl;
	t1.join();
}

// C++11没有设置线程名的函数，但是Windows有一个SetThreadDescription
// Linux 有一个pthread_setname_np
// 设置线程名为 MyThread
GTEST_TEST(TplTests, StdThreadSetName) {
	std::thread t1(process2);

	auto handle = t1.native_handle();
	auto set_res = pthread_setname_np(handle, "MyThread");
	ERROR_CHECK(set_res, "Set thread name successfully!", "Set thread name failed")

	char thread_name[256];
	auto get_res = pthread_getname_np(handle, thread_name, sizeof(thread_name));	
	ERROR_CHECK(get_res, "Get thread name successfully: " << thread_name, 
		"Get thread name failed")

	t1.join();
}

// 这个函数返回系统CPU默认并发数
// 默认线程数应该等于核数，对CPU的利用率高

GTEST_TEST(TplTests, GetHardwareConcurrency)  {
	auto cores = std::thread::hardware_concurrency();
	std::cout << "Hardware concurrency: " << cores << std::endl;
}

GTEST_TEST(TplTests, StdThreadGetIdInSubThread) {
	std::thread t1(process3);
	t1.join();
}







