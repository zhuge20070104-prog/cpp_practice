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
#include <list>
#include <forward_list>

// std::list 
// 1. 以双向链表形式实现
// 2. 在任意位置插入和删除效率较高
// 3. 不提供随机访问
// 记住std::list 是双端链表
// std::list每个节点都需要 一个前向指针和一个后向指针，比较浪费内存
// 如果内存比较紧张，而且不需要双向访问，可以使用std::forward_list （C++11）

// std::forward_list
// 1. 以单向链表形式实现
// 2. 耗用内存较小
// 3. 插入删除效率较高
// 4. 不提供size函数，不能看大小  std::forward_list不能看大小，访问元素都是和插入的反序
// 5. 元素是头插法插入的

//  std::list不允许随机访问，没有重载 []运算符
// 所以只能使用迭代器操作
GTEST_TEST(TplTests, ListUsage) {
	std::list<int> col;
	for(int i=0; i<5; ++i) {
		col.push_back(i*10);
	}

	for(auto it=col.begin(), end=col.end(); it!=end; ++it) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;

	auto it = col.begin();
	col.insert(it, 800);
	ASSERT_LIST_EQ(col.begin(), col.end(),  {800, 0, 10, 20, 30, 40});

	// 插入完成之后，begin变了， 要重新获取begin, 再erase
	it = col.begin();
	col.erase(it);
	
	ASSERT_LIST_EQ(col.begin(), col.end(), {0, 10, 20, 30 ,40});
}

// 在任意位置的插入和删除操作都只需要常量时间，
// 适合频繁的插入和删除
// 但不需要随机访问的场景
GTEST_TEST(TplTests, ForwardListUsage) {
	std::forward_list<int> col;
	for(int i=0; i<10; ++i) {
		col.push_front(i);
	}

	// 反向打印
	for(auto x: col) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	ASSERT_LIST_EQ(col.begin(), col.end(), {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
	col.insert_after(col.begin(), 10);
	ASSERT_LIST_EQ(col.begin(), col.end(), {9, 10, 8, 7, 6, 5, 4, 3, 2, 1, 0});
	col.erase_after(col.begin());
	ASSERT_LIST_EQ(col.begin(), col.end(), {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
}
// 插入在第一个后面，他不知道前一个元素是啥，它只知道后一个元素是啥，单向的链表
// 删除也是删除当前元素的后面一个元素




























