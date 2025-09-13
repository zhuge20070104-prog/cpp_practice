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

std::list<int> g_data;
int constexpr Size = 2000000;
std::mutex g_mutex; 

// std::lock_guard 资源获取即初始化，
// 获取就lock
// 析构就unlock
void download() {
	for(int i=0; i<Size; ++i) {
		std::lock_guard<std::mutex> lock(g_mutex);
		g_data.push_back(i);
	}
}

void download2() {
	for(int i=0; i<Size; ++i) {
		std::lock_guard<std::mutex> lock(g_mutex);
		g_data.push_back(i);
	}
}

// 在使用std::mutex lock之时，一个线程锁住之后，另一个线程一直处于等待状态
// 即使CPU处于idle状态，另一个线程也在等待。
// 这样没有充分利用CPU资源，所以我们必须尽量不使用锁
GTEST_TEST(TplTests, StdLockGuard) {
	std::thread th_download(download);
	std::thread th_download2(download2);
	th_download.join();
	th_download2.join();
}

void download_list(std::promise<std::list<int>>&& proms) {
	std::list<int> l1;
	for(int i=0; i<Size; ++i) {
		l1.push_back(i);
	}
	proms.set_value(l1);
}

void download_list2(std::promise<std::list<int>>&& proms) {
	std::list<int> l2;
	for(int i=0; i<Size; ++i) {
		l2.push_back(i);
	}
	proms.set_value(l2);
}

// 这个问题的第二个解法是，
// 每个线程分配一个list，
// 等所有线程join执行完毕之后
// 对所有list进行拷贝，拷贝到global list中
// 这样将会大大提高程序效率
GTEST_TEST(TplTests, MultipleListNoLock) {
	std::promise<std::list<int>> proms1;
	std::promise<std::list<int>> proms2;
	auto fut1 = proms1.get_future();
	auto fut2 = proms2.get_future();
	std::thread th_download(download_list, std::move(proms1));
	std::thread th_download2(download_list2, std::move(proms2));
	th_download.join();
	th_download2.join();
	auto l1 = fut1.get();
	auto l2 = fut2.get();
	std::vector<int> res;
	res.resize(l1.size() + l2.size());
	std::copy(l1.begin(), l1.end(), res.begin());
	std::copy(l2.begin(), l2.end(), res.begin()+l1.size());
}

