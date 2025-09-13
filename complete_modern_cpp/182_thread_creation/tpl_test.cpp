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


// std::thread
// 1. 接受一个可调用对象作为构造函数参数
// 2. 可调用对象在单独的线程执行
// 3. 构造函数不会等待线程启动，它立即return
// 4. 定义在thread头文件中

std::list<int> g_data;
int constexpr Size = 5000000;

void download() {
	std::cout << "[Downloader] Started download" << std::endl;
	for(int i=0; i<Size; ++i) {
		g_data.push_back(i);
	}
	std::cout << "[Downloader] Finished download" << std::endl;
}

void write_file() {
	std::ofstream ofs {"result.txt"};
	for(int i=0; i<300; ++i) {
		ofs <<"Hello" << i << "\n";
	}
	ofs.close();
}


// 主线程立马执行完毕，然后退出，不会等待子线程执行完毕
// 所以我们需要调用子线程的join，等待子线程退出
// 主线程消息立即打印，等待子线程结束
GTEST_TEST(TplTests, SubThreadJoin) {
	std::cout << "[main] User started an operation" << std::endl;
	std::thread th_download(download);
	std::cout << "[main] User started another operation" << std::endl;
	th_download.join();
}

GTEST_TEST(TplTests, SubThreadDetach) {
	std::cout << "[main] User started an operation" << std::endl;
	std::thread th_download(download);
	// detach放到后台去执行， detach的线程没法join
	th_download.detach();

	std::cout << "[main] User started another operation" << std::endl;
	if(th_download.joinable()) {
		std::cout << "Joinable, join" << std::endl;
		th_download.join();
	}

	// detach之后,子线程没有再执行的机会
	// std::cin >> ch 暂停程序执行
	// detach 之后的thread 会自动释放相应资源
	char ch;
	std::cin >> ch;
}

GTEST_TEST(TplTests, TestDetach2) {
	std::cout << "[main] User started an operation" << std::endl;
	std::thread th_write_file(write_file);
	// detach放到后台去执行， detach的线程没法join
	th_write_file.detach();

	std::cout << "[main] User started another operation" << std::endl;
	std::this_thread::sleep_for(std::chrono::microseconds(1000));
}