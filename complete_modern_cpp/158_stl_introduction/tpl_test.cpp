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
#include <type_traits>


GTEST_TEST(TplTests, STLIntroduction) {
	// 标准模板库
	// 1. C++ 标准库的核心
	// 2. 由HewLett Packard的Alexander Stepenov和Meng Lee开发
	// 3. 提供快速的，可复用的容器和算法
	// 4. 依赖于模板实现，几乎STL里面的每一个组件都是模板
	
	
	// 核心组件
	//  1. 容器类，算法和迭代器形成了STL的核心组件
	//  2. 容器类代表数据，算法代表数据上的可用操作
	//  3. 迭代器是容器和算法之间的纽带
	//  4. 也包含并发，随机数，正则表达式和工具类等等

	// 为何使用STL
	//  1. 快速开发
	//  2. 可靠
	//  3. 可移植
	//  4. 高效&快速
	//  5. 精确
	//  6. 可读性高的代码
	//  7. 较低的维护成本

	// 容器类型
	// 顺序容器
	//  array  vector list deque forward_list
	// 关联容器
	// set multiset  map multimap
	// 无序容器
	// unordered_set unordered_multiset
	// unordered_map unordered_multimap

	// Common functions
	// 1. 默认构造函数
	// 2. 统一初始化构造函数
	// 3. 拷贝构造函数
	// 4. 基于迭代器的构造函数，用于从其他容器构建对象
	// 5. size clear begin end
	// 6. 默认内存管理器 default allocator
	std::cout << "Hello STL" << std::endl;
}
























