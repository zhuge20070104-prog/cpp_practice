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


// 类型萃取
// 1.  类型萃取提供在编译期提取类型的能力
// 			在编译期获取类型的特征
//  		转换类型的属性
// 2.  在模板元编程中非常有用
// 3.  在检视类型时，要么返回boolean，要么返回一个类型
// 4.  在头文件中提供基于模板的接口 <type_traits>
// 5.  有些类型萃取依赖于编译器
//    	 	编译器为这些特性提供内部函数
// type_traits 支持的函数链接:  https://en.cppreference.com/w/cpp/header/type_traits

// 整型除法会出错，我们只想看到浮点型相除的结果
// 非浮点数不让除
template <typename T>
T divide(T a, T b) {
	if(!std::is_floating_point<T>::value) {
		std::cout << "Use floating point types only" << std::endl;
		return 0;
	}
	return a/b;
}

template <typename T>
void check(T&&) {
	std::cout << std::boolalpha;
	std::cout << "Is Reference?" << std::is_reference<T>::value << std::endl;

	// 类型转换traits返回一个 type值，而不是value,返回一个全新类型，
	// 像这种复合类型，为了让编译器知道这是一个类型，需要在前面加上typename关键字
	std::cout << "After removing reference: " <<
		std::is_reference<typename std::remove_reference<T>::type>::value 
		<< std::endl;
}

// 判断是否是整数类型
GTEST_TEST(TplTests, IsIntergalTest) {
	ASSERT_TRUE(std::is_integral<int>::value);
}

GTEST_TEST(TplTests, FloatingPtDivide) {
	ASSERT_EQ(divide(5, 2), 0);
	ASSERT_EQ(divide(5.0, 2.0), 2.5);
}

GTEST_TEST(TplTests, Check) {
	// 5是一个纯右值，不是引用类型，value是引用类型
	check(5);
	int value{};
	check(value);
}








