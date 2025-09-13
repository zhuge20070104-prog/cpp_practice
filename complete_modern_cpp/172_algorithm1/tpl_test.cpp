#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>
// 包含algorithm头文件才能使用STL算法


// 用户对象，容器
// 1. 如果用户定义的对象要被加入容器，编译器可能会定义一些规则
// 2. 这些大多是一些操作符，这些操作符必须被用户对象重载
// 3. 通常情况下，你的对象必须重载下列操作符  <, >, !=, ==
// 4. 不同的容器使用这些操作符进行查找和排序
// 5. 并不是必须得
// 可以自己写函数对象，实现这些操作符


// 算法
// 1. STL 提供通用任务的算法，
//  排序，删除，查找，数字化等等
// 2. STL算法比手写循环有更多优化
// 3. 不管何种数据类型，对所有容器都适用
// 4. 一些算法能够通过用户定义的操作符进行自定义
// 5. 一些容器提供特殊版本的算法
//  list类提供sort和remove算法
// 关联容器提供lower_bound, upper_bound, find算法等等
// 大多数算法定义在algorithm头文件中


// std::unordered_set, std::unordered_multiset
// set::unordered_map, std::unordered_multimap
// 需要给自定义对象重写两个函数
// 自定义hash函数对象
// 自定义equal方法


// Employee class包含三个属性
// name, id, programming_language
class Employee {
	std::string name;
	int id;
	std::string prog_lan;

public:
	Employee(std::string const& name_, int id_, std::string const& prog_lan_):
		name(name_),
		id(id_),
		prog_lan(prog_lan_) {

	}

	std::string const& get_name() const {
		return name;
	}

	int get_id() const {
		return id;
	}

	std::string const& get_programming_language() const {
		return prog_lan;
	}

	// Employee按照id排序，这样std::sort算子就可以在std::vector上工作了
	bool operator<(Employee const& other) const {
		return id < other.id;
	}

	friend std::ostream& operator<<(std::ostream& os, Employee const& emp) {
		os << emp.get_id() << " --> " << emp.get_name() << " --> " << emp.get_programming_language();
		os << "\n";
		return os;
	}
};

GTEST_TEST(TplTests, VectorSortByEmployee) {
	std::vector<Employee> v {
		Employee{"Umar", 101, "C++"},
		Employee{"Bob", 202, "Java"},
		Employee{"Joey", 200, "Python"}
	};

	std::sort(v.begin(), v.end());
	print(v);	
}

GTEST_TEST(TplTests, VectorCompareCallback) {
	std::vector<Employee> v {
		Employee{"Umar", 101, "C++"},
		Employee{"Bob", 202, "Java"},
		Employee{"Joey", 200, "Python"}
	};

	// 除了重载 < 操作符，也可以传递比较Callback，也可以做比较
	std::sort(v.begin(), v.end(), [](Employee const& e1, Employee const& e2){
		return e1.get_name() < e2.get_name();
	}); 

	print(v);
}

struct EmployeeGreaterCompare {
	bool operator()(Employee const& e1, Employee const& e2) const {
		return e1.get_id() > e2.get_id();
	}
};

GTEST_TEST(TplTests, StdSetFuncObj) {
	// set::set 也需要比较函数，可以重载 < 操作符，也可以自己写函数对象
	std::set<Employee, EmployeeGreaterCompare> s {
		Employee{"Umar", 101, "C++"},
		Employee{"Bob", 202, "Java"},
		Employee{"Joey", 200, "Python"}
	};

	print(s);
}

