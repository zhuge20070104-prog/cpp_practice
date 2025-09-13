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


// 数组的引用，可以传大小

// 这个函数对char const*类型的arr无法排序，因为会比较char*指针的大小
// 不是字符串的大小，可能需要做模板特化，但是模板特化为了一个比大小的operator，重写一个函数，不大合适
template <typename T, std::size_t size> 
void sort(T (&arr) [size]) {
	for(std::size_t i=0; i<size-1; ++i) {
		for(std::size_t j=0; j<size-1; ++j) {
			if(arr[j] > arr[j+1]) {
				// 用户自定义类会产生多次拷贝，这里使用移动语义，避免拷贝
				T temp = std::move(arr[j]);
				arr[j] = std::move(arr[j+1]);
				arr[j+1] = std::move(temp);
			}
		}
	}
}


template <typename T>
using Comparator = bool (*) (T, T);
// 使用一个predicator，由用户传入predicator，就可以解决特殊类比较的问题
// 函数指针做回调的问题，
// 1. 编译器无法优化函数指针，没法对地址调用做内联，
// 2. 函数指针无法保存对象状态，因为函数指针是全局函数，就算把状态保存到变量中，状态也是共享的。
// 也可以使用函数对象做回调函数
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

GTEST_TEST(TplTests, SimpleSort) {
	int arr[] {1, 6, 8, 4, 0};
	print(arr);
	// 默认升序
	sort(arr);
	print(arr);
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










