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
#include "stack.hpp"


GTEST_TEST(TplTests, TestVaradicArgsPrint) {
	auto s = MAKE_STACK(float, 10);
	s.push(3);
	s.push(1);
	s.push(6);
	s.push(9);
	// 验证拷贝构造函数可用
	auto s2(s);
	while(!s2.empty()) {
		std::cout << s2.top() << " ";
		s2.pop();
	}
	std::cout << std::endl;
}

