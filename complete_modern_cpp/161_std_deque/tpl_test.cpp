#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <deque>

// std::deque
// deque是double end queue的缩写
// 1. 在双端插入/删除时比较高效
// 2. 自动增长
// 3. 支持随机访问迭代器
// 4. 任意位置插入/删除不大理想，需要移动元素

// Deque 可以 push_back，也可以push_front
GTEST_TEST(TplTests, DequePushFrontAndBack) {
	std::deque<int> col;
	for(int i=0; i<5; ++i) {
		col.push_back(i*10);
	}
	for(int i=0; i<5; ++i) {
		col.push_front(i*10);
	}

	for(auto it=col.begin(), end=col.end(); it!=end; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	ASSERT_LIST_EQ(col.begin(), col.end(), {40, 30, 20, 10, 0, 0, 10, 20, 30, 40});
}

// Deque还可以pop_front
GTEST_TEST(TplTests, DequePopFrontAndBack) {
	std::deque<int> col;
	for(int i=0; i<5; ++i) {
		col.push_back(i*10);
	}
	for(int i=0; i<5; ++i) {
		col.push_front(i*10);
	}
	col.pop_back();
	col.pop_front();
	ASSERT_LIST_EQ(col.begin(), col.end(), {30, 20, 10, 0, 0, 10, 20, 30});
}




























