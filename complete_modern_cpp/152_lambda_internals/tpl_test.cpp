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

struct UnamedNoTemp {
	int operator()(int x, int y) const {
		return x + y;
	}
};

template <typename T>
struct Unamed {
	T operator()(T x, T y) const {
		return x + y;
	}
};

GTEST_TEST(TplTests, ExplictReturnTypeTest) {
	// 返回不同的类型的话，double和int，需要显示指定返回值，
	// 如果只需要返回一种类型的话，不需要显示指定，type deduction 就可以
	auto sum = [](int x, int y) -> double {
		if(true) 
			return 5.0;
		return x + y;
	};
	std::cout << "Sum is: " << sum(1, 1) << std::endl;
}


// 带参数的lambda表达式
GTEST_TEST(TplTests, LambdaWithParams) {
	auto sum = [](int x, int y) {
		return x + y;
	};

	std::cout << "Sum is: " << sum(5, 2) << std::endl;
}

GTEST_TEST(TplTests, LambdaInternalWithoutTemplate) {
	UnamedNoTemp u;
	// lambda表达式的内部实现其实就是UnamedNoTemp
	std::cout << "Sum is: " << u(5, 2) << std::endl;
} 


GTEST_TEST(TplTests, LambdaAutoParamC14) {
	auto sum = [](auto x, auto y) {
		return x + y; 
	};

	// 可以加任何类型，这里加float类型
	std::cout << "Sum is: " << sum(5.5f, 2.2f) << std::endl;
}


GTEST_TEST(TplTests, LambdaAutoLamdaTemp) {
	// Auto 参数的lambda 表达式相当于这个
	Unamed<float> u;
	std::cout << "Sum is: " << u(5.5f, 2.2f) << std::endl;
}

GTEST_TEST(TplTests, LambdaNoExcept) {
	// 该函数不抛出异常
	auto sum = [](auto x, auto y) noexcept {
		return x + y;
	};
	std::cout << "Sum is: " << sum(5.5f, 2.2f) << std::endl;
}

GTEST_TEST(TplTests, LambdaExcept) {
	// 该函数可能抛出异常
	auto sum = [](auto x, auto y) noexcept(false) {
		return x + y;
	};
	std::cout << "Sum is: " << sum(5.5f, 2.2f) << std::endl;
}











