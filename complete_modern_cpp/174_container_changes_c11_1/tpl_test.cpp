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
#include "integer.h"

// C++11 容器变化
// 1. 所有创建迭代器的函数都被标成了 noexcept
// 2. 容器类添加新成员函数，例如emplace, emplace_front, emplace_back，支持初始化列表
// 3. 容器能感知 move 操作，优先使用move，不使用拷贝
// 4. std::vector容器添加新函数， data() shrink_to_fit()
// 5. 顺序容器添加std::erase函数
// 6. 关联容器添加新函数， emplace_hint,extract,contains

// C++11 可以使用初始化列表初始化所有容器, 之前必须使用 insert和push_back才行
GTEST_TEST(TplTests, InitializerList) {
	std::vector<int> v_int {1, 2, 3, 4};
	print(v_int);
}

GTEST_TEST(TplTests, PushBackTest) {
	std::vector<Integer> v_int;
	// push_back需要调用两次构造函数，构造函数和移动构造函数
	v_int.push_back(5);   
} 

GTEST_TEST(TplTests, EmplaceBackTest) {
	std::vector<Integer> v_int;
	// emplace_back 就地构造，不用移动 
	v_int.emplace_back(5);
}


// 对于已经存在的对象 push_back和 emplace_back 是一样的, 都会构造两个对象
GTEST_TEST(TplTests, PushBackAlreadyExist) {
	std::vector<Integer> v_int;
	Integer val {5};
	v_int.push_back(val); 
}

GTEST_TEST(TplTests, EmplaceBackAlreadyExist) {
	std::vector<Integer> v_int;
	Integer val {5};
	v_int.emplace_back(val); 
}


// emplace_back 语法也更简单，直接传入参数，在容器中构造即可
GTEST_TEST(TplTests, EmplaceBackEasyToUse) {
	std::vector<std::pair<int, std::string>> data;
	data.push_back(std::make_pair(100, "C++"));
	data.emplace_back(200, "Java"); 
}


