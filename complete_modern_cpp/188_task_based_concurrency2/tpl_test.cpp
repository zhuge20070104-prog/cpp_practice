#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <chrono>
#include <fstream>
#include <list>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <future>
#include <pthread.h>
#include <boost/type_index.hpp>

// std::async
// 1. 高级别并发的一部分
// 2. 在一个单独的线程中执行一个可调用对象或者一个函数
// 3. 返回一个std::future对象用来获取可调用对象的结果
// 4. 包含future头文件来使用std::async
GTEST_TEST(TplTests, StdAsyncDoc) {

// std::async的调用形式
// 1. std::future<return_type> std::async(Callable, args)
// 2. std::future<return_type> std::async(launch_policy, Callable, args)


// Launch Policy
// 1. 你可以指定下面的启动策略 [launch policy]
// a) std::launch::deferred - task同步执行
// b) std::launch::async - task异步执行
// 2. 不带launch policy来调用std::async函数可能并不会产生一个新线程
// a) 取决于编译器的实现
// b) 想要强制std::async异步执行任务，需要显示指定std::launch::async
// 3. 如果新线程使用std::launch::async创建失败，将会抛出std::system_error异常

// 任务参数，返回值
// 1. std::async启动任务时可以指定参数
// 2. 默认，参数是值传递的方式传递的
// 3. 为了以引用方式传递参数，可以采用引用包装，std::ref
//  如果想要传递常量引用，请使用std::cref
// 4. 从任务返回一个值，直接从相应的函数返回就够了
// 5. 该值通过std::future对象带回

// std::future
// 1. 用于线程之间的通信
// 2. 有一个共享的状态可以在不同的线程中访问
// 3. 通过一个std::promise对象创建一个std::future对象
// a). std::async创建一个std::promise对象，这个std::promise对象直接返回一个std::future对象
// b). std::promise是输入通道
// c). std::future是输出通道
// std::promise存放共享数据，std::future读取共享数据
// 读取共享数据的线程会等待std::future ready再读
// 4. 读取共享数据的线程会等待std::future ready再读
// 5. promise和future对 允许线程之间安全的数据共享

}






