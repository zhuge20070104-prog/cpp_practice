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

// 这段代码的两个问题
// 1. 对i的访问超出了test的生命周期，进入了main函数的生命周期
// 这将会导致一个dangling reference错误
// 这个可以通过将join函数移动到test 内部解决
// 2. 所有线程共享同一个i的引用，线程看到的i值与线程启动的先后顺序有关
// 这种情况叫data race。
void test(std::vector<std::thread>& workers) {
    for(int i=0; i<8; ++i) {
        // aout << "Address of i in main: " << &i << "\n";
        auto th = std::thread(&the_func, std::ref(i));
        workers.push_back(std::move(th));
        // move之后资源被偷取，不能join了
        assert(!th.joinable());
    }

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
    return EXIT_SUCCESS;
}