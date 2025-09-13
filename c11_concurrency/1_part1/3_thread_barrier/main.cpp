#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include "asyc_out.hpp"

int main(int argc, char* argv[]) {
    std::vector<std::thread> workers;
    for(int i=0; i<10; ++i) {
        workers.push_back(std::thread([i](){
            aout << "Hello from thread: " << i << "!\n";
        }));
    }

    // 每次运行 Hello from main的执行时机都不一样，充满了不确定性
    // Hello from thread 还有可能被截断
    // 我们希望每次的运行结果都一样
    aout << "Hello from main!\n";
    std::for_each(workers.begin(), workers.end(), [](std::thread& th) {
        th.join();
    });
  
    return EXIT_SUCCESS;
}