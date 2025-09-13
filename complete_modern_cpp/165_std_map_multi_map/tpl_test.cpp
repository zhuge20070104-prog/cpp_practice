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
#include <map>
#include <functional>

// std::map 和 std::multimap
// 1. 内部以二叉树形式实现
// 2. 存储一个键值对
// 3. 元素存储时根据key进行排序
// 4. 查找比较快速
// 5. 不能随机访问
// 6. keys 不能直接修改

//  初始化列表构造map
GTEST_TEST(TplTests, StdMapInitializerList) {
	// std::map 存储的是std::pair对象，他不是直接存储的key value
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	print(m);
}

GTEST_TEST(TplTests, StdMapInsert) {
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	// std::map 插入元素的4种方法
	// 1. 初始化列表
	// 2. 构造std::pair
	// 3. 使用std::make_pair
	// 4. 利用重载的[] 运算符
	m.insert(std::pair<int, std::string>(8, "Aquaman"));
	m.insert(std::make_pair(6, "Wonder Woman"));
	m[0] = "Flash";
	print(m);
} 

GTEST_TEST(TplTests, StdMapPrint) {
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	std::cout << "Print Using iterator" << std::endl;
	// 使用迭代器打印map中的所有元素
	for(auto  it=m.begin(), end=m.end(); it!=end; ++it) {
		std::cout << it->first << " ---> " << it->second << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Using range-based for loop" << std::endl;

	// 使用range-based for loop 打印map中的所有元素
	// 内部元素已经按key进行排序了
	for(auto const& p: m) {
		std::cout << p.first << " ---> " << p.second << std::endl;
	}
}

GTEST_TEST(TplTests, ModifyAndErase) {
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	// key不能修改，但是value可以修改
	m[0] = "Flash";
	m[0] = "Kid Flash";
	print(m);

	// 可以使用erase函数删除 pair
	m.erase(0);
	print(m);
}

GTEST_TEST(TplTests, StdMapFind) {
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	// map的查找，find方法，查找成功
	auto iter = m.find(1);
	if(iter != m.end()) {
		std::cout << "Found: " << iter->second << std::endl;
	} else {
		std::cout << "Not Found" << std::endl;
	}
}

GTEST_TEST(TplTests, ReadBrakets) {
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};
	// 中括号运算符除了写还可以读
	std::cout << m[1] << std::endl;
	ASSERT_EQ(m[1], "Superman");
}

GTEST_TEST(TplTests, AccessNonExistKey) {
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	// 尝试访问不存在的key，会添加一个key，value为default value
	std::cout << "10: " << m[10] << std::endl;
	print(m);
}

GTEST_TEST(TplTests, InsertDuplicateKey) {
	std::map<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};
	// 插相同的key插不进去，只会保留老的值
	m.insert(std::make_pair(6, "Wonder Woman"));
	m.insert(std::make_pair(6, "Power Girl"));
	print(m);
}

GTEST_TEST(TplTests, StdMultiMapSameKey) {
	std::multimap<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	// std::multimap支持相同的key,这两个可以work
	m.insert(std::make_pair(6, "Wonder woman"));
	m.insert(std::make_pair(6, "Power Girl"));

	print(m);
}

GTEST_TEST(TplTests, StdMultiMapEqualRange) {
	std::multimap<int, std::string> m {
		{1, "Superman"},
		{2, "Batman"},
		{3, "Green Lantern"}
	};

	m.insert(std::make_pair(6, "Wonder woman"));
	m.insert(std::make_pair(6, "Power Girl"));

	// std::multimap::equal_range用法，
	// first是第一个匹配key的pair, second是第一个不匹配key的pair
	// 所以在循环内部要继续 found.first->first, found.first->second
	auto found = m.equal_range(6);
	while(found.first != found.second) {
		std::cout << found.first->first << " ---> " << found.first->second << std::endl;
		++found.first;
	}

}