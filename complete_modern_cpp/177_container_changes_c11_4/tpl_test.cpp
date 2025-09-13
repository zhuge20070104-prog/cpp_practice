#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>
#include "integer.h"

template <typename IT, typename Val>
std::vector<IT> find_elements(IT start, IT end, Val val) {
	std::vector<IT> results;
	auto it = start;
	while(it!=end) {
		if(*it == val) results.push_back(it);
		++it;
	}
	return results;
} 


//  std::list可以直接按元素值remove元素
// std::vector只能按迭代器，元素索引remove
// 为了让顺序容器也能remove,C++20添加了std::erase函数
// 可以直接按值对顺序容器remove
GTEST_TEST(TplTests, CPP20StdErase) {
	std::vector<int> v_int{1, 2, 3, 4, 2};
	std::list<int> l_int{1, 2, 3, 4, 2};
	std::deque<int> d_int{1, 2, 3, 4, 2};
	auto v_it_range = find_elements(v_int.begin(), v_int.end(), 2);
	// 注意，必须反着删，不然会导致迭代器失效
	std::for_each(v_it_range.rbegin(), v_it_range.rend(), [&v_int](auto it) {
		v_int.erase(it);
	});
	
	l_int.remove(2);

	auto d_it_range = find_elements(d_int.begin(), d_int.end(), 2);
	std::for_each(d_it_range.rbegin(), d_it_range.rend(), [&d_int](auto it) {
		d_int.erase(it);
	});

	print(v_int);
	print(l_int);
	print(d_int);
}

