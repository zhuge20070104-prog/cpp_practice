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


void downloader() {
	using namespace std::chrono_literals;
	for(int i=0; i<10; ++i) {
		std::cout << ".";
		std::cout.flush();
		// 300ms字面量，代表300ms，
		// 1s，代表1秒
		// 字面量在C++14中引入
		std::this_thread::sleep_for(300ms);
	}
}

// std:async的第一个参数是要调用的函数，后面可以传递函数需要的参数
// 必须获取返回的std::future对象，否则会阻塞主线程运行，变成同步的效果

// 这个std::async的线程怎么来，取决于编译器的具体实现
GTEST_TEST(TplTests, StdThreadGetIdInSubThread) {
	std::future<void> result = std::async(std::launch::async, downloader);
	std::cout << "Main() threading continues executing...\n";
	result.wait();

	// std::async(std::launch::async, downloader);
	// std::cout << "Main() threading continues executing...\n";

}






