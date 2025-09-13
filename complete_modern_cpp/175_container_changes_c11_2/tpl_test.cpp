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


// 默认应该是原地构造，不调用拷贝和移动构造函数
// 但是在v_int.emplace_back(2) 之后发生了vector重新分配内存
// 重新分配内存的时候，需要调用移动/拷贝构造函数，把元素重新拷贝到新分配的容器中
// 如果想要编译器调用移动构造函数，需要保证移动构造函数不发生异常，否则移动过程发生异常，将破坏容器的完整性
// 因为可能一部分元素已经移动过了
GTEST_TEST(TplTests, NoExceptMoveTest) {
	std::vector<Integer> v_int;
	// 默认应该原地构造，但是如果reallocate之后，就需要重新拷贝了

	// 给Integer类的移动构造函数和移动赋值操作符重载添加noexcept之后，就会调用移动构造函数了
	// 因为保证了 移动操作不会抛出异常，破坏容器的完整性

	// 添加noexcept标记的时候需要注意，头文件和实现文件都需要添加noexcept标记，两个函数除了std::cout以外，
	// 其他部分都不会发生异常
	v_int.emplace_back(1);
	v_int.emplace_back(2);
	v_int.emplace_back(3);
}



