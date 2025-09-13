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

// 一个fake的String类，用来计算创建对象的个数
class String {
public:
	String() {
		std::cout << "String()" << std::endl;
	}

	String(String const&) {
		std::cout << "String(String const&)" << std::endl;
	}

	String& operator=(String const&) {
		std::cout << "String& operator=(String const&)" << std::endl;
		return *this;
	}

	~String() {
		std::cout << "~String()" << std::endl;
	}
};

std::list<int> g_data;
int constexpr Size = 5000000;

void download(std::string file_name) {
	std::cout << "[Downloader] Started download of file: " << file_name << std::endl;
	for(int i=0; i<Size; ++i) {
		g_data.push_back(i);
	}
	std::cout << "[Downloader] Finished download" << std::endl;
}

void down_load_by_ref(String& file_name) {
	std::cout << "[Downloader] Started download of file: " << std::endl;
	for(int i=0; i<Size; ++i) {
		g_data.push_back(i);
	}
	std::cout << "[Downloader] Finished download" << std::endl;
}

void down_load_by_cref(String const& file_name) {
	std::cout << "[Downloader] Started download of file: " << std::endl;
	for(int i=0; i<Size; ++i) {
		g_data.push_back(i);
	}
	std::cout << "[Downloader] Finished download" << std::endl;
}


// std::thread类的构造函数是一个变长参数，如果传递多余的参数，多余的参数会传递给线程函数
GTEST_TEST(TplTests, PassByValue) {
	std::string file_name{"cppcast.mp4"};
	std::cout << "[main] User started an operation" << std::endl;
	std::thread th_download(download, file_name);
	std::cout << "[main] User started another operation" << std::endl;
	if(th_download.joinable()) {
		th_download.join();
	}
}

GTEST_TEST(TplTests, PassByRef) {
	String file_name;
	std::cout << "[main] User started an operation" << std::endl;
	// 直接传递String对象，会导致拷贝构造函数被调用，String被拷贝了
	// 必须使用std::ref传递引用，才能保证参数不被拷贝
	std::thread th_download(down_load_by_ref, std::ref(file_name));
	std::cout << "[main] User started another operation" << std::endl;
	if(th_download.joinable()) {
		th_download.join();
	}
}


GTEST_TEST(TplTests, PassByCRef) {
	String file_name;
	std::cout << "[main] User started an operation" << std::endl;

	// 传递常量引用请使用std::cref
	std::thread th_download(down_load_by_cref, std::cref(file_name));
	std::cout << "[main] User started another operation" << std::endl;
	if(th_download.joinable()) {
		th_download.join();
	}
}

