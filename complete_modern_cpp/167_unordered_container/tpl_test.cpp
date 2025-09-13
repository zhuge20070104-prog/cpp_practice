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
#include <map>
#include <functional>



GTEST_TEST(TplTests, StdUnorderedContainer) {
	// 相当于Java的HashSet和HashMap
	// Unordered Containers无序容器
	// 1. 以Hash表形式实现的关联容器
	// 2. 值通过Hash函数进行Hash，并且以未定义的顺序存储
	// 3. 快速查找，插入，删除，但是在一段时间内可能会退化
	// 4. std::unordered_set 存储用来hash的key值
	// 5. std::unordered_map存储pairs值 (first部分用来计算Hash)
	// 6. 迭代器都是常量迭代器

}