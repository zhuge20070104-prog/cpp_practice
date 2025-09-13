#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <list>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>
#include "contact.h"

//  C++ 并发
// 1.大型应用程序有多个组件
// 2. 某些组件可能必须并发执行
// 3. 这允许有效的使用CPU
// 4. 并发可以通过创建多个线程来实现
// 5. C++11添加了并发支持
// 6. 包含了启动和管理线程的工具
std::list<int> g_data;
int constexpr Size = 5000000;

void download() {
	std::cout << "[Downloader] Started download" << std::endl;
	for(int i=0; i<Size; ++i) {
		g_data.push_back(i);
	}
	std::cout << "[Downloader] Finished download" << std::endl;
}


//  耗时操作
// 顺序执行，单线程，非多线程
//  完全顺序执行，要等待一个任务完成，才能开始另一个任务
GTEST_TEST(TplTests, ProgamTakesLongTimeInMain) {
	std::cout << "[main] User started an operation" << std::endl;
	download();
	std::cout << "[main] User started another operation" << std::endl;
}