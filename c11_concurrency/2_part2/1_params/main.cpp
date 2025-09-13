#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include "asyc_out.hpp"

void the_func(int i) {
    aout << "Hi from worker " << i << "!\n";
} 

// 除了join, 还有一种让线程不结束的方法，就是detach, detach会产生一个daemon进程
// daemon进程在后台运行，由运行时接管，无法控制线程何时结束。不太可靠
int main(int argc, char* argv[]) {  
    std::vector<std::thread> workers;
    for(int i=0; i<8; ++i) {
        auto th = std::thread(&the_func, i);
        workers.push_back(std::move(th));
        // move之后资源被偷取，不能join了
        assert(!th.joinable());
    }

    std::cout << "Hi from main!\n";

    std::for_each(workers.begin(), workers.end(), [](std::thread& th) {
        assert(th.joinable());
        th.join();
    });
    return EXIT_SUCCESS;
}