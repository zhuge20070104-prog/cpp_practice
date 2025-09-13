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
#include "print.hpp"


GTEST_TEST(TplTests, TestVaradicArgsPrint) {
	// 可变模板参数 递归调用过程，每调用一次，参数个数减少一个
	print(1, 2.5, 3, "4");
}

