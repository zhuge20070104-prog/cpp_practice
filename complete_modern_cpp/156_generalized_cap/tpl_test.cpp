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

//  生成式捕获(C++14)
//	1. 这个特性允许在捕获表达式中创建新的变量
//  2. 这些变量的类型从被捕获的表达式类型推导出来
//  3. 这些变量必须被初始化
//  4. 如果初始化表达式是一个变量，这个变量的名字可以和 初始化的变量相同或不同
//  5. 生成式引用捕获需要加上 & [&var=expression](args)

GTEST_TEST(TplTests, SimpleValueCapture) {
	int x {5};
	// y = x，生成捕获，输出10
	auto f = [y=x](int arg) {
		return y + arg;
	};
	std::cout << f(5) << std::endl;
	ASSERT_EQ(f(5), 10);
}


GTEST_TEST(TplTests, MoveCapture) {
	std::fstream out {"./file.txt", std::ios::out};
	// move完了以后只在这个作用域有效，超过这个函数就无效了
	auto write = [out=std::move(out)](int x) mutable {
		out << x;
	};

	write(200);
}
























