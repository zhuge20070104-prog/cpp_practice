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

// 类型定义 typedef 
// 1. 为一个存在的类型引入一个名字
// 2. 这个名字是对应类型的同义词
// 3. 可用于为已经存在的类型创建短的，更有意义的名字
// 4. 简化一些类型的声明，例如函数指针，或者模板等
// 5. 可能修改的实现细节可以被封装起来 (C++标准库实现了很多typedef,例如 std::string std::iostream等)
// 6. 并不创建一个新类型，只是为已经存在的类型指定一个新的名字


class Employee {};

// typedef namespace, 避免重名
namespace TD {
	typedef unsigned int UINT;
	typedef long long LLONG;
	typedef std::vector<std::list<Employee>> Teams;
	typedef char const* (*ErrorFn)(int);

	// typedef 不能做模板化， type alias 可以做模板化
	typedef std::vector<std::list<std::string>> Names;
}



// 类型别名
// 1. 已知类型的一个同义名字
// 2. 不引入新类型
// 3. 跟typedef 的用法相同
// 4. 通过 using关键字实现

// using's namespace, 避免重名
namespace US {
	using UINT =  unsigned int;
	using LLONG = long long;
	using Teams = std::vector<std::list<Employee>>;
	using ErrorFn = char const* (*) (int);
	template <typename T>
	using Names = std::vector<std::list<T>>;

	// 也可以直接预绑定一个类型
	using NameStr = std::vector<std::list<std::string>>;
}


char const* get_error_message(int err_no) {
	return "empty";
}


void show_error(US::ErrorFn pfn, int error_no) {
	std::cout << pfn(error_no) << std::endl;
}

GTEST_TEST(TplTests, UsingTest) {
	US::Names<std::string> names;
	US::ErrorFn errorFn = get_error_message;
	show_error(errorFn, 1);
	US::UINT val {};
	US::LLONG ele {};
	US::Teams testing_teams;
	US::Teams::iterator it = testing_teams.begin();
}

GTEST_TEST(TplTests, TDTest) {
	TD::Names names;
	TD::ErrorFn errorFn = get_error_message;
	show_error(errorFn, 1);
	TD::UINT val {};
	TD::LLONG ele {};
	TD::Teams testing_teams;
	TD::Teams::iterator it = testing_teams.begin();
}


