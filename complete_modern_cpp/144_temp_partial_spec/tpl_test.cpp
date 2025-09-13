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


// 模板的部分特化是指对一部分模板做特化，对另外一部分模板不做特化
// 在这里加一个列模板，表示打印多少列
template <typename T, int columns>
class PrettyPrinter {
	T* m_pdata;
public:
	PrettyPrinter(T* data): m_pdata(data) {
	}

	void print() {
		std::cout << "Columns: " << columns << std::endl;
		std::cout << "{" << *m_pdata << "}" << std::endl;
	}

	T* get_data() {
		return m_pdata;
	}
};

// 假设当columns=80时，是一种特殊的设备，我们想要以一种特殊的方式进行打印
// 才能看到比较好的格式化效果,就是要对columns=80进行特化
template <typename T>
class PrettyPrinter<T, 80> {
	T* m_pdata;
public:
	PrettyPrinter(T* data): m_pdata(data) {}

	void print() {
		std::cout << "Using 80 columns" << std::endl;
		std::cout << "{" << *m_pdata << "}" << std::endl;
	}

	T* get_data() {
		return m_pdata;
	}
};


template <typename T>
class SmartPointer {
	T* m_ptr;
public:
	SmartPointer(T* ptr): m_ptr(ptr) {
	}

	T* operator->() {
		return m_ptr;
	}

	T& operator*() {
		return *m_ptr;
	}

	~SmartPointer() {
		delete m_ptr;
	}
};


// 基于Array的智能指针模板特化
template <typename T>
class SmartPointer<T[]> {
	T* m_ptr;
public:
	SmartPointer(T* ptr): m_ptr(ptr) {

	}

	T& operator[](int index) {
		return m_ptr[index];
	}

	~SmartPointer() {
		delete [] m_ptr;
	}
};

GTEST_TEST(TplTests, CommonPrint) {
	int data = 800;
	PrettyPrinter<int, 40> p {&data};
	p.print();
}

GTEST_TEST(TplTests, Print80) {
	int data = 800;
	// columns值为80时的部分特化
	PrettyPrinter<int, 80> p(&data);
	p.print();
}

GTEST_TEST(TplTests, SimplePointer) {
	SmartPointer<int> p1(new int(3));
	ASSERT_EQ(*p1, 3);
}

GTEST_TEST(TplTests, ArrayPointerSpec) {
	SmartPointer<int[]> p2(new int[5]);
	p2[0] = 5;
	ASSERT_EQ(p2[0], 5);
}