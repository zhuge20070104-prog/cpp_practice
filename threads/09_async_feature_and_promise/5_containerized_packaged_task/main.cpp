#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <future>
#include <vector>
#include <functional>

void packaged_int_int() {
    std::vector<std::packaged_task<int(int)>> tasks;
    std::vector<std::thread> threads;

    int hardware_concurrency = std::thread::hardware_concurrency();
    int task_count = hardware_concurrency? hardware_concurrency: 2; 
    for(int i=0; i<task_count; ++i) {
        std::packaged_task<int(int)> pt ([](int a) {
            printf("Origin result: %d\n", a);
            return a+1;
        });
        tasks.push_back(std::move(pt));
    }
    
    for(int i=0; i<task_count; ++i) {
        auto task = std::move(tasks[i]);
        auto fut = task.get_future();
        std::thread t(std::move(task), i);
        threads.push_back(std::move(t));
        printf("Future result: %d\n", fut.get());
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

void packaged_void_void() {
    std::vector<std::packaged_task<void(void)>> tasks;
    std::vector<std::thread> threads;

    int hardware_concurrency = std::thread::hardware_concurrency();
    int task_count = hardware_concurrency? hardware_concurrency: 2; 
    for(int i=0; i<task_count; ++i) {
        std::packaged_task<void(void)> pt ([i]() {
            printf("void(void) result: %d\n", i+2);
        });
        tasks.push_back(std::move(pt));
    }
    
    for(int i=0; i<task_count; ++i) {
        auto task = std::move(tasks[i]);
        auto fut = task.get_future();
        std::thread t(std::move(task));
        threads.push_back(std::move(t));
        fut.wait();
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main(int argc, char* argv[]) {
    packaged_int_int();
    packaged_void_void();
    return EXIT_SUCCESS;
}