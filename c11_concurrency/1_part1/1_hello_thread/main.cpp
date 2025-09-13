#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>

// 创建线程有一定的overhead，导致Hi from main会先执行。
void thread_func() {
    std::cout << "Hi from thread!\n";
}

int main(int argc, char* argv[]) {
    std::thread th(&thread_func);
    std::cout << "Hi from main!\n";
    th.join();
    return EXIT_SUCCESS;
}