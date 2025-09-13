#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>

std::mutex mtx;

void job1() {
    mtx.lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        std::cout << "job1 is executed..." << std::endl;
    mtx.unlock();
}

// 演示try_lock的第二个分支，失败分支
void job2() {
    if(mtx.try_lock()) {
        std::cout << "job2 is executed..." << std::endl;
        mtx.unlock();
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if(mtx.try_lock()) {
            std::cout << "job2 executed on second try\n";
            mtx.unlock();
        }
    }
}

int main(int argc, char* argv[]) {
    std::thread t1(&job1);
    std::thread t2(&job2);

    t1.join();
    t2.join();
    return EXIT_SUCCESS;    
}