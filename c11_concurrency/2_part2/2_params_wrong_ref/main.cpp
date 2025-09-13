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

// 使用std::ref显示声明，我们要以引用方式传递
int main(int argc, char* argv[]) {  
    std::vector<std::thread> workers;
    for(int i=0; i<8; ++i) {
        // aout << "Address of i in main: " << &i << "\n";
        auto th = std::thread(&the_func, std::ref(i));
        workers.push_back(std::move(th));
        // move之后资源被偷取，不能join了
        assert(!th.joinable());
    }

    aout << "Hi from main!\n";

    std::for_each(workers.begin(), workers.end(), [](std::thread& th) {
        assert(th.joinable());
        th.join();
    });
    return EXIT_SUCCESS;
}