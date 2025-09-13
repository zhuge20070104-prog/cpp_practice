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

std::list<int> g_data;
int constexpr Size = 10000;

void download() {
	for(int i=0; i<Size; ++i) {
		g_data.push_back(i);
	}
}

void download2() {
	for(int i=0; i<Size; ++i) {
		g_data.push_back(i);
	}
}

// 我们想加快速度，多线程同时下载
// 下载完成之后，打印一下list大小
// 元素个数不是20000，是19917，有问题
// 当一个线程往std::list里面写数据的时候，另一个线程也同时在写，
// 这个时候std::list还来不及改变他的大小来容纳新线程写入的数据，就会出现数据丢失
// 这样每一次运行程序，出现元素的个数和结果都不一样
// 这种情况叫竟态, data race
GTEST_TEST(TplTests, DataRace) {
	std::thread th_download(download);
	std::thread th_download2(download2);
	th_download.join();
	th_download2.join();
	std::cout << g_data.size() << std::endl;
}

std::list<int> g_data2;
std::mutex g_mutex;
// 使用std::mutex做线程同步，需要先包含mutex头文件
// 然后构建std::mutex对象
// 在处理竟态操作时，首先使用mutex::lock获取锁，这样其他线程就没法获取锁了
// 而是被放在一个等待队列里面，
// 等到竟态操作完成以后，使用mutex::unlock解锁，其他队列里的等待线程就能获取锁了
void download_with_mutex() {
	for(int i=0; i<Size; ++i) {
		g_mutex.lock();
		g_data2.push_back(i);
		g_mutex.unlock();
	}
}

void download_with_mutex2() {
	for(int i=0; i<Size; ++i) {
		g_mutex.lock();
		g_data2.push_back(i);
		g_mutex.unlock();
	}
}



GTEST_TEST(TplTests, SyncWithMutex) {
	std::thread th_download(download_with_mutex);
	std::thread th_download2(download_with_mutex2);
	th_download.join();
	th_download2.join();
	std::cout << g_data2.size() << std::endl;
}

std::list<int> g_data3;
std::mutex g_mutex1;
void download_with_error() {
	for(int i=0; i<Size; ++i) {
		g_mutex1.lock();
		g_data3.push_back(i);
		// i=500 的时候return, lock之后无法unlock,
		// 这样可能造成死锁
		if(i==500) {
			return;
		}
		g_mutex1.unlock();
	}
}

void download_with_error2() {
	for(int i=0; i<Size; ++i) {
		g_mutex1.lock();
		g_data3.push_back(i);
		g_mutex1.unlock();
	}
}

// 程序卡死了，
// 原因是，第一个线程锁住mutex之后，返回了，没有做unlock操作，第一个线程死掉了
// 第二个线程一直在等待第一个线程解锁。这样他一直等待，这种情况叫死锁
// 我们必须保证锁住的锁，能够被解锁
GTEST_TEST(TplTests, SyncDeadLock) {
	std::thread th_download(download_with_error);
	std::thread th_download2(download_with_error2);
	th_download.join();
	th_download2.join();
	std::cout << g_data3.size() << std::endl;
}
