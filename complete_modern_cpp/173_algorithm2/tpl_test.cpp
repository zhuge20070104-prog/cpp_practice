#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>

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

	bool operator==(Employee const& emp) const {
		return get_programming_language() == emp.get_programming_language();
	}

	friend std::ostream& operator<<(std::ostream& os, Employee const& emp) {
		os << emp.get_id() << " --> " << emp.get_name() << " --> " << emp.get_programming_language();
		os << "\n";
		return os;
	}
};

// 使用range-based for loop 检测有多少employee了解C++
GTEST_TEST(TplTests, FindElementByRangeBasedForLoop) {
	std::vector<Employee> v {
		Employee {"Umar", 101, "C++"},
		Employee {"Bob", 202, "Java"},
		Employee {"Joey", 200, "C++"}
	};

	int cpp_count {};
	for(auto const& e: v) {
		if(e.get_programming_language() == "C++") {
			++cpp_count;
		}
	}
	std::cout << "CPP Count: " << cpp_count << std::endl;
	ASSERT_EQ(cpp_count, 2);
}


// STL 里面提供了一个count算子用来做同样的事情，计算雇员里面了解C++的个数，这样会比较清晰一点
// std::count内部使用 == 操作符比较元素是否相等，必须对Employee重载 == 操作符
// 才能使用 count
GTEST_TEST(TplTests, FindElementByCount) {
	std::vector<Employee> v {
		Employee {"Umar", 101, "C++"},
		Employee {"Bob", 202, "Java"},
		Employee {"Joey", 200, "C++"}
	};

	auto cpp_count = std::count(v.begin(), v.end(), Employee{"", 0, "C++"});
	std::cout << "CPP Count: " << cpp_count << std::endl;
	ASSERT_EQ(cpp_count, 2);
}

// 也可以使用std::count_if,他接受一个谓词作为第三个参数
// 这样就可以随意改写谓词了
GTEST_TEST(TplTests, FindElementByCountIf) {
	std::vector<Employee> v {
		Employee {"Umar", 101, "C++"},
		Employee {"Bob", 202, "Java"},
		Employee {"Joey", 200, "C++"}
	};

	auto cpp_count = std::count_if(v.begin(), v.end(), [](Employee const& emp){
		return emp.get_programming_language() == "C++";
	});
	std::cout << "CPP Count: " << cpp_count << std::endl;
	ASSERT_EQ(cpp_count, 2);
}


// 查找第一个Java工程师，返回第一个匹配的元素的迭代器， std::find_if
GTEST_TEST(TplTests, FindElementByFindIf) {
	std::vector<Employee> v {
		Employee {"Umar", 101, "C++"},
		Employee {"Bob", 202, "Java"},
		Employee {"Joey", 200, "C++"}
	};

	auto emp_it = std::find_if(v.begin(), v.end(), [](Employee const& emp){
		return emp.get_programming_language() == "Java";
	});
	
	if(emp_it != v.end()) {
		std::cout << *emp_it << std::endl;
	}

	ASSERT_EQ(emp_it->get_id(), 202);
	ASSERT_EQ(emp_it->get_name(), "Bob");
	ASSERT_EQ(emp_it->get_programming_language(), "Java");
}

//  std::for_each打印所有Employee的名字
GTEST_TEST(TplTests, ForEachBasicUsage) {
	std::vector<Employee> v {
		Employee {"Umar", 101, "C++"},
		Employee {"Bob", 202, "Java"},
		Employee {"Joey", 200, "C++"}
	};

	std::for_each(v.begin(), v.end(), [](auto const& emp) {
		std::cout << emp.get_name() << std::endl;
	});
}


struct EmployeeResult {
	std::vector<Employee> results;
	// 获取所有C++ Employee
	void operator()(Employee const& emp) {
		if(emp.get_programming_language() == "C++") {
			results.push_back(emp);
		}
	}
};

// std::for_each 可以返回传入的函数对象
GTEST_TEST(TplTests, ForEachAdvancedUsage) {
	std::vector<Employee> v {
		Employee {"Umar", 101, "C++"},
		Employee {"Bob", 202, "Java"},
		Employee {"Joey", 200, "C++"}
	};

	auto emp_results = std::for_each(v.begin(), v.end(), EmployeeResult());
	for(auto const& emp: emp_results.results) {
		std::cout << emp << std::endl;
	}
}

