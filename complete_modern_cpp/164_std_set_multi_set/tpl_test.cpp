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
#include <set>
#include <functional>
// std::greater和std::less是函数对象，他们在functional头文件中



// std::set和std::multi_set
// 1. 内部以二叉树形式实现
// 2. 元素在内部以排序方式存储
// 3. value就是key
// 4. 查找迅速
// 5. 不能随机访问
// 6. 元素不能被直接修改

// set对插入和删除效率不如list高，但是对查找和检索效率高，
// 当你需要频繁检索的时候，记住使用set

// set内部是二叉排序树，
// 所以set会有序存储
// set既不能push_back，也不能push_front，set只能insert
GTEST_TEST(TplTests, StdSetSimpleInsert) {
	std::set<int> s {8, 2, 0, 9, 5};
	s.insert(1);
	s.insert(3);

	for(auto it=s.begin(), end=s.end(); it!=end; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	ASSERT_LIST_EQ(s.begin(), s.end(), {0, 1, 2, 3, 5, 8, 9});
}

GTEST_TEST(TplTests, StdSetCantModifyIterator) {
	std::set<int> s{8, 2, 0, 9, 5};
	auto it = s.begin();
	// const iterator不能写，只能读，编译错误
	// *it = 9;
	while(it!=s.end()) {
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
	ASSERT_LIST_EQ(s.begin(), s.end(), {0, 2, 5, 8, 9});
}

GTEST_TEST(TplTests, StdSetEraseTest) {
	std::set<int> s{8, 2, 0, 9, 5};
	std::cout << "Before: " << std::endl;
	print(s);
	ASSERT_LIST_EQ(s.begin(), s.end() , {0, 2, 5, 8, 9});

	s.erase(0);  // s.erase(T value) 通过值删除
	s.erase(s.begin()); // 通过迭代器删除
	std::cout << "After: " << std::endl;
	print(s);
	ASSERT_LIST_EQ(s.begin(), s.end(), {5, 8, 9});
}

// 查找元素，返回元素位置迭代器
GTEST_TEST(TplTests, StdSetFindTest) {
	std::set<int> s{8, 2, 0, 9, 5};
	auto it = s.find(9);
	if(it != s.end()) {
		std::cout << "Element Found" << std::endl;
	} else {
		std::cout << "Not Found" << std::endl; 
	}

	ASSERT_TRUE(it!=s.end());
}

// 改变std::set的默认排序
GTEST_TEST(TplTests, StdSetChangeSortOrder) {
	std::set<int, std::greater<int>> s{8, 2, 0, 9, 5};
	print(s);
	ASSERT_LIST_EQ(s.begin(), s.end(), {9, 8, 5, 2, 0});
}

// std::set不允许重复元素，添加重复元素将会看不到，会被忽略
// std::multiset允许添加重复元素
GTEST_TEST(TplTests, StdMultisetEqualRange) {
	std::multiset<int, std::greater<int>> s {8, 2, 0, 9, 5};
	s.insert(1);
	s.insert(3);
	s.insert(3);
	s.insert(3);
	print(s);
	ASSERT_LIST_EQ(s.begin(), s.end(), {9, 8, 5, 3, 3, 3, 2, 1, 0});

	// equal_range返回一个std::pair<Iterator, Iterator>, 如果找到了，第一个iterator表示第一个匹配的元素
	// 第二个iterator表示第一个不匹配的元素
	// 如果没有找到，两个iterator都指向end
	auto found_range = s.equal_range(3);
	while(found_range.first != found_range.second) {
		std::cout << *found_range.first++ << " ";
	}
	std::cout << std::endl;
}

































