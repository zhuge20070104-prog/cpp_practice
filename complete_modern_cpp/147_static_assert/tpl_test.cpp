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

// static_assert的用法
// C++ 本身有一个assert函数，assert失败后会调用abort终止程序，但是这个assert是运行时的
// 1. static_assert 是一种新的计算表达式的方法
// 2. 接受一个表达式或者用户定义的消息
// 3. 用于在编译期测试表达式
// 4. 如果表达式return false, 编译器显示指定的消息，并且编译失败


template <typename T>
T divide(T a, T b) {
	static_assert(std::is_floating_point<T>::value, "Only floating point type supported");
	return a/b;
}

GTEST_TEST(TplTests, CommonSizeOfTest) {
	if(sizeof(void*) != 4) {
		std::cout << "not 32 bit mode" << std::endl;
		return;
	}
	std::cout << "Handle 32 bit mode" << std::endl;
}


GTEST_TEST(TplTests, SizeOfStaticAssert) {
	// 编译期错误，Compile in 32 bit only
	// static_assert(sizeof(void*) == 4, "Compile in 32-bit only");
}

GTEST_TEST(TplTests, DivideStaticAssert) {
	// 编译期错误，Only floating point type supported
	// std::cout << divide(5, 2) << std::endl;
}









