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

template <typename IT, typename Callback>
void ForEach(IT first, IT last, Callback callback) {
	while(first != last) {
		callback(*first);
		++first;
	}
}

// 捕获列表模式
// 1. [var]  值捕获var
// 2. [=] 值捕获所有当前环境变量
// 3. [&var] 引用捕获var
// 4. [&] 引用捕获当前环境所有变量
// 5. [&, var] 值捕获var, 其他变量引用捕获
// 6. [=, &var] 引用捕获var，其他变量值捕获
// 7. [this] 捕获this指针，捕获当前对象的所有成员变量

GTEST_TEST(TplTests,  ValueCaptureNotChange) {
	int arr[] {1, 2, 4, 0, 8};
	int sum{};
	// sum值捕获，没有修改，结果为0
	ForEach(std::begin(arr), std::end(arr), [sum](auto x) mutable {
		sum+=x;
	});

	std::cout << sum << std::endl;
	ASSERT_EQ(sum, 0);
}

GTEST_TEST(TplTests, RefCaptureChange) {
	int arr[] {1, 2, 4, 0, 8};
	int sum{};

	// 可以使用引用捕获来修改值
	ForEach(std::begin(arr), std::end(arr), [&sum](auto x) {
		sum += x;
	});

	std::cout << sum << std::endl;
	ASSERT_EQ(sum, 15);
}

GTEST_TEST(TplTests, RefCaptureAll) {
	int arr[] {1, 2, 4, 0, 8};

	int sum{};
	// 引用捕获所有变量, &
	ForEach(std::begin(arr), std::end(arr), [&](auto x) {
		sum += x;
	});

	ASSERT_EQ(sum, 15);
}

// lambda 表达式只能捕获在其之前定义的变量，后面的不行
GTEST_TEST(TplTests, ValueCaptureAll) {
	int arr[] {1, 2, 4, 0, 8};
	int sum{};

	// 值捕获所有变量, = 
	ForEach(std::begin(arr), std::end(arr), [=](auto x) mutable{	
		sum += x;
	});

	ASSERT_EQ(sum, 0);
}

GTEST_TEST(TplTests, MixCaptureRefSum) {
	int arr[] {1, 2, 4, 0, 8};
	int sum{};

	// 其他变量值捕获，引用捕获sum
	ForEach(std::begin(arr), std::end(arr), [=, &sum](auto x) {
		sum += x;
	});

	ASSERT_EQ(sum, 15);
}


GTEST_TEST(TplTests, MixCaptureValueSum) {
	int arr[] {1, 2, 4, 0, 8};
	int sum{};

	// 其他变量引用捕获，值捕获sum
	ForEach(std::begin(arr), std::end(arr), [&, sum](auto x) mutable {
		sum += x;
	});

	ASSERT_EQ(sum, 0);
}


























