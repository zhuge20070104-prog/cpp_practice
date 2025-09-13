#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <future>
#include <chrono>
#include "asyc_out.hpp"


void the_func() {    
    using namespace std::chrono_literals;
    std::cout << "Starting task\n";
    std::this_thread::sleep_for(8s);
    std::cout << "Ending task\n";
}


// 也可以不使用ftr.get，ftr的析构函数 会等待线程结束
int main(int argc, char* argv[]) {  
    std::future<void> ftr = std::async(&the_func);
    std::cout << "Hello from main!\n";

    ftr.get();
    return EXIT_SUCCESS;
}