#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include "asyc_out.hpp"

void the_func(int & i) {
    // aout << "Address of i in the_func: " << &i << "\n";
    aout << "Hi from worker " << i << "!\n";
} 

// Hi from worker3 出现了两次，还有一些垃圾数据，
// i 是临时变量，从test的for循环出来以后就不存在了，而且i一直在变
// 线程传递引用的第一个危险，生命周期问题
void test(std::vector<std::thread>&  workers) {
    for(int i=0; i<8; ++i) {
        auto th = std::thread(&the_func, std::ref(i));
        workers.push_back(std::move(th));
        // move之后资源被偷取，不能join了
        assert(!th.joinable());
    }
}

void join_threads(std::vector<std::thread>& workers) {
    std::for_each(workers.begin(), workers.end(), [](std::thread& th) {
        assert(th.joinable());
        th.join();
    });
}

// 使用std::ref显示声明，我们要以引用方式传递
int main(int argc, char* argv[]) {  
    std::vector<std::thread> workers;
    test(workers);
    aout << "Hi from main!\n";
    join_threads(workers);
    return EXIT_SUCCESS;
}