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

template <typename T, std::size_t size, typename Comparator>
void sort(T (&arr)[size], Comparator comp) {
	for(std::size_t i=0; i<size-1; ++i) {
		for(std::size_t j=0; j<size-1; ++j) {
			if(comp(arr[j], arr[j+1])) {
				T temp = std::move(arr[j]);
				arr[j] = std::move(arr[j+1]);
				arr[j+1] = std::move(temp);
			}
		}
	}
}

// ForEach 遍历每个元素，应用callback
template <typename T, std::size_t size, typename Callback>
void ForEach(T (&arr) [size], Callback callback) {
	for(std::size_t i=0; i<size; ++i) {
		callback(arr[i]);
	}
}

template <typename T>
struct Unamed {
	T offset;

	Unamed(T off): offset(off) {

	}

	void operator()(T& x) const {
		x += offset;
		// 这是一个const函数， 不能修改成员变量
		// ++ offset;
	}
};



// 使用lambda 表达式定义函数对象的两个优势，
// 1. 用户一眼就能看到这个函数干嘛的
// 2. 不用定义函数和函数对象，污染名称空间
GTEST_TEST(TplTests, LambdaCallback) {
	int arr[] {1, 6, 8, 4, 0};
	for(auto const ele: arr) {
		std::cout << ele << " ";
	}
	std::cout << std::endl;

	sort(arr, [](auto x, auto y) {
		return x > y;
	});
	
	ASSERT_LIST_EQ(std::begin(arr), std::end(arr), {0, 1, 4, 6, 8});
	for(auto const ele: arr) {
		std::cout << ele << " ";
	}
	std::cout << std::endl;
}

// 使用Auto 承载，在同一个函数里面可以多次调用
GTEST_TEST(tplTests, UsingAutoToRecall) {
	int arr[] {1, 6, 8, 4, 0};
	auto comp = [](auto x, auto y) {
		return x > y;
	};

	sort(arr, comp);
	ASSERT_LIST_EQ(std::begin(arr), std::end(arr), {0, 1, 4, 6, 8});
}


// ForEach打印元素
GTEST_TEST(TplTests, CustomizedForEachPrint) {
	int arr[] {1, 6, 8, 4, 0};
	ForEach(arr, [](auto x) {
		std::cout << x << " ";
	});
	std::cout << std::endl;
}

// 按值捕获变量
GTEST_TEST(TplTests, ValueCaptureAddOffset) {
	int arr[] {1, 6, 8, 4, 0};
	ForEach(arr, [](auto x){
		std::cout << x << " ";
	});
	std::cout << std::endl;

	int offset{5};
	ForEach(arr, [offset]( auto& x) {
		x += offset;
	});

	ForEach(arr, [](auto x){
		std::cout << x << " ";
	});
	std::cout << std::endl;
}

// 使用函数对象实现同样的功能
GTEST_TEST(TplTests, AddOffsetFuncObj) {
	int arr[] {1, 6, 8, 4, 0};
	ForEach(arr, [](auto x){
		std::cout << x << " ";
	});
	std::cout << std::endl;

	Unamed<int> u(5);
	ForEach(arr, u);

	ForEach(arr, [](auto x){
		std::cout << x << " ";
	});
	std::cout << std::endl;
}


GTEST_TEST(TplTests, AddOffsetMutable) {
	int arr[] {1, 6, 8, 4, 0};
	ForEach(arr, [](auto x){
		std::cout << x << " ";
	});
	std::cout << std::endl;

	int offset {0};
	// mutable 去除函数的 const属性
	ForEach(arr, [&offset](auto& x)mutable {
		x += offset;
		++offset;
	});

	ForEach(arr, [](auto x){
		std::cout << x << " ";
	});
	std::cout << std::endl;
}




















