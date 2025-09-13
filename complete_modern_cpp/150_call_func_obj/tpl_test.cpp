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


// 函数对象相关
// 1. 一个重载了函数调用操作符 operator() 的对象
// 2. 调用函数重载操作符会组装一个全局的函数调用
// 3. 可以被用作callback来取代函数指针
// 4. 比函数指针效率更高
// 5. 大部分情况下使用struct 实现

// 函数指针和函数对象的比较
//  函数指针   函数对象
//  1. 通过指针调用   通过对象调用
//  2. 动态调用    静态调用
//  3. 可以运行时指定   必须编译期指定
//  4.  优化困难   易于优化
//  5.  慢        快
//  6.  不能保存状态   可以保存状态

// 函数对象可以内联，内联发生在编译期   

template <typename T>
using Comparator = bool (*) (T, T);

template <typename T, std::size_t size>
void sort(T (&arr) [size], Comparator<T> comp) {
		for(std::size_t i=0; i<size-1; ++i) {
			for(std::size_t j=0; j<size-1; ++j) {
				if(comp(arr[j],  arr[j+1])) {
					T temp = std::move(arr[j]);
					arr[j] = std::move(arr[j+1]);
					arr[j+1] = std::move(temp);
				}
			}
		}
}


// 调用函数对象，需要先构造函数对象，再调用函数
// 实际上是调用comp.operator()(3, 5)
// 函数对象其实是一个语法糖
template <typename T, std::size_t size, typename Comparator>
void sort(T (&arr) [size],  Comparator  comp) {
		for(std::size_t i=0; i<size-1; ++i) {
			for(std::size_t j=0; j<size-1; ++j) {
				if(comp(arr[j],  arr[j+1])) {
					T temp = std::move(arr[j]);
					arr[j] = std::move(arr[j+1]);
					arr[j+1] = std::move(temp);
				}
			}
		}
}

template <typename T>
struct CompareGreator {
	bool operator()(T x, T y) {
		return x > y;
	}
};

template <typename T, std::size_t size>
void print(T (&arr) [size]) {
	for(std::size_t i=0; i<size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
} 

bool greater(int x, int y) {
	return x > y;
}

bool less(int x, int y) {
	return x< y;
}


GTEST_TEST(TplTests, SortWithComp) {
	int arr[] {1, 6, 8, 4, 0};
	print(arr);
	// 升序
	sort(arr, greater);
	print(arr);

	// 降序
	sort(arr, less);
	print(arr);
}

GTEST_TEST(TplTests, SortWithFunctionObj) {
	CompareGreator<int> comp_greator;
	int arr[] {1, 6, 8, 4, 0};
	print(arr);
	// 升序
	// 直接传递函数对象进行比较，比较时会调用重载的operator()操作符
	sort(arr, comp_greator);
	print(arr);
}










