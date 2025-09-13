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

std::string const FileName = "../tpl_test.cpp"; 

// Capacity 是说容器不再增长能放的最大元素数，size是说容器里面已经有了多少元素
GTEST_TEST(TplTests, SizeAndCapacity) {
	std::vector<int> v_int;
	for(std::size_t i=0; i<100; ++i) {
		v_int.emplace_back(i);
	}

	// Capacity: 128, Size:100
	std::cout << "Size: " << v_int.size() << std::endl;
	std::cout << "Capacity: " << v_int.capacity() << std::endl;
}

GTEST_TEST(TplTests, EraseAndShrinkToFit) {
	std::vector<int> v_int;
	for(std::size_t i=0; i<100; ++i) {
		v_int.emplace_back(i);
	}
	std::cout << "Size: " << v_int.size() << std::endl;
	std::cout << "Capacity: " << v_int.capacity() << std::endl;

	// 删除90个元素之后，容量不会自动减少
	v_int.erase(v_int.begin(), v_int.end()-10);
	std::cout << "After Erase: " << std::endl;
	std::cout << "Size: " << v_int.size() << std::endl;
	std::cout << "Capacity: " << v_int.capacity() << std::endl;

	// shrink_to_fit 可以让容量和大小相等
	v_int.shrink_to_fit();
	std::cout << "After Erase, Shrink to fit: " << std::endl;
	std::cout << "Size: " << v_int.size() << std::endl;
	std::cout << "Capacity: " << v_int.capacity() << std::endl;
	ASSERT_EQ(v_int.size(), 10);
	ASSERT_EQ(v_int.capacity(), 10);
}



GTEST_TEST(TplTests, RawBufCharArray) {
	std::ifstream input{FileName};
	if(!input) {
		std::cout << "Could not open file\n";
		return;
	}
	// 四部曲
	// 1. 获取文件大小
	// 2. 动态分配内存
	// 3. 再读取
	// 4. 最后释放

	// boost::filesystem 也可以使用std::filesystem替代 C++17 standard
	auto size = boost::filesystem::file_size(FileName);
	char* buf = new char[size];
	input.read(buf, size);
	std::cout << buf << std::endl;
	delete [] buf;
	input.close();
}


// C++11 新特性 vector::data
// 使用std::vector管理内存，不用手动管理
GTEST_TEST(TplTests, VectorBufCharArray) {
	std::ifstream input{FileName};
	if(!input) {
		std::cout << "Could not open file\n";
		return;
	}

	auto size = boost::filesystem::file_size(FileName);
	std::vector<char> buffer;
	buffer.resize(size);
	
	input.read(buffer.data(), size);
	std::cout << buffer.data() << std::endl;
	input.close();
}

// std::string也可以动态管理内存
// 有一点需要注意，不要触发underflow, 或者overflow
// 也就是说要留好足够的内存
GTEST_TEST(TplTests, StringBufCharArray) {
	std::ifstream input{FileName};
	if(!input) {
		std::cout << "Could not open file\n";
		return;
	}

	auto size = boost::filesystem::file_size(FileName);
	std::string buffer;
	buffer.resize(size);
	input.read(buffer.data(), size);
	std::cout << buffer.data() << std::endl;
	input.close();
}

