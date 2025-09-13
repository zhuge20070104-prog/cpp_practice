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

// 成员变量和静态变量都是自动捕获的
// 只有局部变量需要手动捕获
class Product {
	std::string name;
	float price;

public:
	Product(std::string const& name_, float price_): name(name_), price(price_) {}

	void assign_final_price() {
		float taxes[] {12, 5, 5};

		float base_price {price};

		ForEach(std::begin(taxes), std::end(taxes), [base_price, this] (float tax) {
			float taxed_price = base_price * tax / 100;
			price += taxed_price;
		});
	}

	float get_price() const {
		return price;
	}
};

GTEST_TEST(TplTests, CaptureClass) {
	Product watch {"Watch", 500};
	watch.assign_final_price();
	std::cout << watch.get_price() << std::endl;
}

// lambda 表达式可嵌套，输出10
GTEST_TEST(TplTests, NestedLambda) {
	[](int x) {
		x *= 2;
		[](int x) {
			std::cout << x << std::endl;
		}(x);
	}(5);
}

// 捕获列表为空时， lambda表达式可以转换为函数指针，函数指针可以用来做回调函数
// Lambda表达式做回调函数不能有捕获列表
// 原理，空捕获列表的lambda表达式，重载了类型转换操作符，可以转换成一个函数指针
// 这个转换操作符返回一个静态的函数指针， 这个函数指针会调用内部的operator() 操作符重载
// 这样这个函数指针就起到了回调函数的作用
// 带捕获列表的就不行
GTEST_TEST(TplTests, LambdaCallback) {
	atexit([]() {
		std::cout << "Program is exiting..." << std::endl;
	});
}

























