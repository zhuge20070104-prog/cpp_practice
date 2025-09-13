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
#include <array>

// std::array
// 1. C style 静态数组的简单封装
// 2. 支持迭代器
// 3. 知道自己的大小
// 4. 支持随机访问迭代器
// 5. 可以和C函数一起使用
// 6. 大小在编译期确定，无法改变

// 迭代器
// 1. 像指针一样的对象
// 2. 用来通过位置访问对应的元素
// 3. 提供重载操作符，例如 ++, -- , * 等
// 4. 在所有容器中都可以通过begin, end函数创建
// end代表最后一个元素的后一个元素，不要尝试解引用end, end常用来指示算法失败

GTEST_TEST(TplTests, ArraySize) {
	std::array<int, 5> arr {3, 1, 8, 5 ,9};
	// std::array知道他自己的大小
	for(std::size_t i=0; i<arr.size(); ++i) {
		arr[i] = i;
	}
	ASSERT_LIST_EQ(arr.begin(), arr.end(), {0, 1, 2, 3, 4});
}

GTEST_TEST(TplTests, ArrayIterator) {
	std::array<int, 5> arr {3, 1, 8, 5, 9};

	for(auto it=arr.begin(), end=arr.end(); it!=end; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// Range based for loop， 内部使用begin和end迭代器
	for(auto const ele: arr) {
		std::cout << ele << " ";
	}
	std::cout << std::endl;
}

// arr.data() 可以返回内部维护的C数组的指针
GTEST_TEST(TplTests, ArrayGetData) {
	std::array<int, 5> arr {3, 1, 8, 5, 9};
	int *r_arr = arr.data();
	ASSERT_LIST_EQ(r_arr, r_arr+5, {3, 1, 8, 5, 9});
}
























