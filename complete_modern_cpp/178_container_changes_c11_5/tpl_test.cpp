#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <set>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>


// 插入时先把迭代器移动到正确的位置，再用emplace_hint，会提高效率
// 详见上面的链接
// 在靠近begin的位置插入 0 
// 就地构造，不产生拷贝: Inserts a new element to the container as close as possible to the position just before hint. 
// The element is constructed in-place, i.e. no copy or move operations are performed.
// Link: https://en.cppreference.com/w/cpp/container/map/emplace_hint 
GTEST_TEST(TplTests, StdSetEmplaceHint) {
	std::set<int> data {1, 2, 6, 3};
	data.emplace_hint(data.begin(), 0);
	print(data);
}

// 原先查找元素 是否存在的方法比较笨重，C++20增加了contains做同样的事儿，返回bool
GTEST_TEST(TplTests, StdSetFind) {
	std::set<int> data {1, 2, 6, 3};
	auto it = data.find(6);
	if(it != data.end()) {
		std::cout << "Found" << std::endl;
	}
}

// 我们想要把第一个字符换成 U 怎么办？Umar
// 直接拿到迭代器的引用，然后修改是不行的，因为这是一个const_iterator, 不让改
// 因为如果可以改的话，二叉树的索引顺序就变了，二叉树就不可用了
GTEST_TEST(TplTests, ChangeStdSetElements) {
	std::set<std::string> names {"Omar", "Ayaan", "Rahaan"};
	auto it = names.find("Omar");
	// 处理方案： 
	// 找到元素，做一个拷贝赋值
	// 拷贝到新元素中，修改拷贝
	// 删除原有，
	// 插入新的
	auto name = *it;
	name[0] = 'U';
	names.erase(it);
	names.insert(name);
	print(names);
}

// 方案2， 获取底层元素
// 改变底层元素值，回插回去
// node是 noncopyable的，只能move
GTEST_TEST(TplTests, ChangeStdSetElements2) {
	std::set<std::string> names {"Omar", "Ayaan", "Rahaan"};
	auto it = names.find("Omar");
	auto node = names.extract(it);
	std::cout << "Node_value: " << node.value() << std::endl;
	node.value()[0] = 'U';
	names.insert(std::move(node));
	print(names);
}
