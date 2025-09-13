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

// lambda 表达式
// 1. 定义一个匿名函数对象
// 2. 函数对象的语法糖
// 3. 可以被作为参数传递
// 4. 可以接受参数和返回值

// 5. 典型的，用来封装若干行代码
// 6. 调用的时候和普通函数一样
// 7. 可用于替代函数对象
// 8. 内部使用匿名函数对象实现
// 9. 使用auto 来提供一个显式的名称


GTEST_TEST(TplTests, InvokeLambdaTest) {
	// 匿名lambda 函数体
	// () 调用匿名lambda函数
	[]() {
		std::cout << "Welcome to lambda expressions" << std::endl;
	}();
}

GTEST_TEST(TplTests, AutoLambdaTest) {
	// 使用auto 获取一个lambda表达式对象，其实就是函数对象，
	// fn调用函数对象
	auto fn = []() {
		std::cout << "Welcome to lambda expressions" << std::endl;
	};
	fn();
}

GTEST_TEST(TplTests, AutoLambdaTypeTest) {
	auto fn = []() {
		std::cout << "Welcome to lambda expressions" << std::endl;
	};

	fn();
	std::cout << typeid(fn).name() << std::endl;
}








