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


template <typename T>
class PrettyPrinter {
	T* m_pdata;
public:
	PrettyPrinter(T* data): m_pdata(data) {
	}

	// PrettyPrinter类以良好格式打印一个对象
	void print() {
		std::cout << "{" << *m_pdata << "}" << std::endl;
	}

	T* get_data() {
		return m_pdata;
	}
};


template <>
class PrettyPrinter<char> {
	char const* m_pdata;

public:
	PrettyPrinter(char const* data): m_pdata(data) {}

	void print(){
		std::cout << "{" << m_pdata << "}" << std::endl;
	}

	char const* get_data() {
		return m_pdata;
	}
 };
// template 


// 对于std::vector<int>类型来说，并不是所有函数都需要被特化，只有print函数需要特化
// 所以可以单独在模板类外面实现一个std::vector<int>类的print函数的特化
// 注意必须在模板类外面，不是在模板类里面
template <>
void PrettyPrinter<std::vector<int>>::print() {
	std::cout << "{";
	for(auto const& x: *m_pdata) {
		std::cout << x << " ";
	}
	std::cout << "}" << std::endl;
}

// 类成员函数的模板特化必须在名称空间级别实现，不能在类级别实现
// 所以不能将类成员函数模板特化写在类里面，必须写在类外面，让编译器能看到。
GTEST_TEST(TplTests, PrintVector) {
	std::vector<int> v {1, 2, 3, 4, 5};
	PrettyPrinter<std::vector<int>> pv(&v);
	pv.print();
}
