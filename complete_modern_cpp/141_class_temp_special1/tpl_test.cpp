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

GTEST_TEST(TplTests, CommonPrinter) {
	int data {5};
	float f {8.2f};

	PrettyPrinter<int> p1(&data);
	PrettyPrinter<float> p2(&f);
	p1.print();
	p2.print();
}

GTEST_TEST(TplTests, PrintCharStar) {
	char const* hello {"Hello World"};
	//  当模板类型被指定为char* 时，类模板T* m_pdata被展开为char ** m_pdata，是可以work的
	PrettyPrinter<char const*> p_ch(&hello);
	p_ch.print();
}


GTEST_TEST(TplTests, PrintCharStar2) {
	char const* hello {"Hello World"};
	// 这次可以调用特化，不需要取地址了
	PrettyPrinter<char> p_ch(hello);
	p_ch.print();
}

