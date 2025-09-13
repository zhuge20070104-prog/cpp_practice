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
#include <unordered_set>
#include <unordered_map>
#include <functional>


// std::unordered_set 需要引入 unordered_set头文件
// unordered_set打印时，没有顺序
GTEST_TEST(TplTests, StdUnorderedSetContainer) {
	std::unordered_set<std::string> col;
	col.insert("Hulk");
	col.insert("Batman");
	col.insert("Green Lantern");
	col.insert("The Flash");
	col.insert("Wonder Woman");
	col.insert("Iron man");
	col.insert("Wolverine");

	for(auto const& ele: col) {
		std::cout << ele << std::endl;
	}
}

// 元素是分配在bucket指向的不同链表里面的
GTEST_TEST(TplTests, StdUnorderedSetBucket) {
	std::unordered_set<std::string> col;
	col.insert("Hulk");
	col.insert("Batman");
	col.insert("Green Lantern");
	col.insert("The Flash");
	col.insert("Wonder Woman");
	col.insert("Iron man");
	col.insert("Wolverine");

	// col.bucket 获取hash桶号
	for(auto const& ele: col) {
		std::cout << "Bucket #: " << col.bucket(ele) << " contains:  " << ele << std::endl;
	}

	std::cout << "Bucket count: " << col.bucket_count() << std::endl;
	std::cout << "Number of elements: " << col.size() << std::endl;
	std::cout << "Load factor: " << col.load_factor() << std::endl;
}

// 多加几个元素可能会导致桶重新分配，load_factor变低
GTEST_TEST(TplTests, StdUnorderedSetBucketReallocate) {
	std::unordered_set<std::string> col;
	col.insert("Hulk");
	col.insert("Batman");
	col.insert("Green Lantern");
	col.insert("The Flash");
	col.insert("Wonder Woman");
	col.insert("Iron man");
	col.insert("Wolverine");
	col.insert("Dr. Strange");
	col.insert("Hawkman");
	col.insert("Better man");
	col.insert("The day you went away");
	col.insert("papprazz");
	col.insert("I hate myself for loving you");
	col.insert("The Russian");
	col.insert("Loving you");
	col.insert("Earings");
	col.insert("The Good thing");
	for(auto const& ele: col) {
		std::cout << "Bucket #: " << col.bucket(ele) << " contains: " << ele << std::endl;
	}
	std::cout << "Bucket count: " << col.bucket_count() << std::endl;
	std::cout << "Number of elements: " << col.size() << std::endl;
	std::cout <<"Load factor: " << col.load_factor() << std::endl; 
}

// std::unordered_multiset 允许重复，std::unordered_set不允许重复
// 可以看到重复元素被放到同一个hash桶中

// std::unordered_set虽然有hash冲突，会把冲突的hash放到同一个桶中
// 但还是比set快
GTEST_TEST(TplTests, StdUnorderedMultiSet) {
	std::unordered_multiset<std::string> col;
	col.insert("Hulk");
	col.insert("Batman");
	col.insert("Green Lantern");
	col.insert("The Flash");
	col.insert("Wonder Woman");
	col.insert("Iron man");
	col.insert("Iron man");
	col.insert("Iron man");
	col.insert("Wolverine");

	// col.bucket 获取hash桶号
	for(auto const& ele: col) {
		std::cout << "Bucket #: " << col.bucket(ele) << " contains:  " << ele << std::endl;
	}

	std::cout << "Bucket count: " << col.bucket_count() << std::endl;
	std::cout << "Number of elements: " << col.size() << std::endl;
	std::cout << "Load factor: " << col.load_factor() << std::endl;
}

// std::unordered_map的使用需要包含 unordered_map头文件
// std::unordered_map也是用来存放key-value pair
// 其中的key值用来计算hash
GTEST_TEST(TplTests, StdUnorderedMapUsage) {
	std::unordered_map<std::string, std::string> col;
	col["Batman"] = "Brue Wayne";
	col["Superman"] = "Clark Kent";
	col["Hulk"] = "Bruce Banner";

	for(auto const& p: col) {
		std::cout << "Bucket #: " << col.bucket(p.first) << " Key: " << p.first << " Value: " << p.second << std::endl;
	}

	std::cout << "Bucket count: " << col.bucket_count() << std::endl;
	std::cout << "Number of elements: " << col.size() << std::endl;
	std::cout << "Load factor: " << col.load_factor() << std::endl;
}

//  插入重复key的元素需要使用std::unordered_multimap
// 相同key的元素在同一个桶中
GTEST_TEST(TplTests, StdUnorderedMultiMapUsage) {
	std::unordered_multimap<std::string, std::string> col;
	col.insert(std::make_pair("Batman", "Bruce Wayne"));
	col.insert(std::make_pair("Batman", "Matches Malone"));
	col.insert(std::make_pair("Superman", "Clark Kent"));
	col.insert(std::make_pair("Hulk", "Bruce Banner"));

	for(auto const& p: col) {
		std::cout << "Bucket #: " << col.bucket(p.first) << " Key: " << p.first << " Value: " << p.second << std::endl;
	}

	std::cout << "Bucket count: " << col.bucket_count() << std::endl;
	std::cout << "Number of elements: " << col.size() << std::endl;
	std::cout << "Load factor: " << col.load_factor() << std::endl;	
}