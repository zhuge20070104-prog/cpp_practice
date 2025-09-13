#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>


std::mutex mtx;

void job1() {
    if(mtx.try_lock()) {
        std::cout << "job1 is executed..." << std::endl;
        mtx.unlock();
    }
}

void job2() {
    if(mtx.try_lock()) {
        std::cout << "job2 is executed..." << std::endl;
        mtx.unlock();
    }
}

// 他们俩至少有一个被执行一次
int main(int argc, char* argv[]) {
    std::thread t1(&job1);
    std::thread t2(&job2);

    t1.join();
    t2.join();
    return EXIT_SUCCESS;    
}