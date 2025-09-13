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
#include <vector>

// std::vector
// 1. 类似动态数组的行为
// 2. 自动增长
// 3. 在末尾增加和删除比较有效
// 4. 允许随机访问迭代器
// 5. 插入和删除效率低 
// 插入和删除最好在后面插，中间插影响性能，需要移动元素

// 每次push_back之后打印大小，显示自动增长后的大小
GTEST_TEST(TplTests, VectorPrintSize) {
	std::vector<int> col{1, 2, 3, 4};
	for(std::size_t i=0; i<5; ++i) {
		col.push_back(i*10);
		std::cout << col.size() << std::endl;
	}
}

// vector重载了 [] 运算符，可以设置或获取元素
GTEST_TEST(TplTests, VectorBracketsOpReload) {
	std::vector<int> col {1, 2, 3, 4};
	for(std::size_t i=0; i<col.size(); ++i) {
		std::cout << col[i] << " ";
	}
	std::cout << std::endl;
}

// vector的迭代器访问方法
GTEST_TEST(TplTests, VectorIterator) {
	std::vector<int> col {1, 2, 3, 4};
	for(auto it=col.begin(), end=col.end(); it!=end; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

// 插入函数和删除函数效率低，需要移动元素，腾出空间
// 移动元素的过程中可能产生拷贝， 特别是容器中装的是自定义元素时，开销更大
GTEST_TEST(TplTests, VectorInsertAndErase) {
	std::vector<int> col {1, 2, 3, 4};
	col.insert(col.begin(), 700);
	col.erase(col.end() - 2);
	col.pop_back();

	for(auto const& ele: col) {
		std::cout << ele << " ";
	}
	std::cout << std::endl;
	ASSERT_LIST_EQ(col.begin(), col.end(), {700, 1, 2});
}


























