#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <future>
#include "asyc_out.hpp"

void the_func(std::promise<std::string>&& prms) {
    std::string str("Hello from future!");
    prms.set_value(str);
}

// 代码需要注意的两点，
// 1. 因为使用了move语义，所以future 应该在move之前构建
// 2. ftr.get会阻塞，直到线程函数结束
int main(int argc, char* argv[]) {  
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();
    std::thread th(&the_func, std::move(prms));
    std::cout << "Hello from main!\n";
    std::string str = ftr.get();
    std::cout << str << std::endl;
    th.join();
    return EXIT_SUCCESS;
}