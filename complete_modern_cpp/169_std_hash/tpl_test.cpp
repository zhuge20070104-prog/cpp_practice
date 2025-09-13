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
#include <functional>
#include <unordered_set>
#include <boost/functional/hash.hpp>


class Employee {
	std::string name;
	int id;

public:
	Employee(std::string const& name_, int id_): name(name_), id(id_) {
	}

	std::string const& get_name() const {
		return name;
	}

	int get_id() const {
		return id;
	}
};


// 构建EmployeeHash和EmployeeEquality 仿函数对象

// 提供一个自定义的函数对象，计算自定义类型的哈希
//  这个hash函数使用的是boost::hash_combine函数计算哈希
struct EmployeeHash {
	std::size_t operator()(Employee const& emp) const {
		std::size_t hash_res;
		boost::hash_combine(hash_res, emp.get_name());
		boost::hash_combine(hash_res, emp.get_id());\
		std::cout << "Hash Result: " << hash_res << std::endl;
		return hash_res;
	}
};

struct EmployeeEquality {
	bool operator()(Employee const& e1, Employee const& e2) const {
		// 判断Equality的时候，最好用上Hash函数中用到的所有字段
		return e1.get_name() == e2.get_name() && e1.get_id() == e2.get_id();
	}
};

// std::hash是一个模板函数对象，它重载了operator()操作符
// 可以计算任意类型的hash
GTEST_TEST(TplTests, StdHashBasicUsage) {
	std::hash<std::string> h;
	std::cout << "Hash: " << h("Hello") << std::endl;
}

GTEST_TEST(TplTests, BoostHashCombine) {
	// 在std::unordered_set中使用构造好的函数对象
	std::unordered_set<Employee, EmployeeHash, EmployeeEquality> col;
	col.insert(Employee{"Umar", 123});
	col.insert(Employee{"Bob", 678});
	col.insert(Employee{"Joey", 612});

	for(auto const& emp: col) {
		std::cout << emp.get_id() << ": " << emp.get_name() << std::endl;
	}
}