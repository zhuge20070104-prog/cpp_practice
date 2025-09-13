#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>
#include <memory>

int shared_value = 0;

void shared_value_increment() {
    ++shared_value;
}

int main(int argc, char* argv[]) {
    int thread_size = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(thread_size);
    for(int i=0; i<thread_size; ++i) {
        threads.push_back(std::thread(&shared_value_increment));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return EXIT_SUCCESS;    
}