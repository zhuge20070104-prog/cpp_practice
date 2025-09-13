#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>

int shared_value = 0;
std::mutex  lock;
void shared_value_increment() {
    lock.lock();
        ++shared_value;
    lock.unlock();
}

int main(int argc, char* argv[]) {

    std::vector<std::thread> threads;
    int thread_size = std::thread::hardware_concurrency();  
    thread_size = thread_size ? thread_size: 2;
    for(int i=0; i<thread_size; ++i) {
        threads.push_back(std::thread(shared_value_increment));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    std::cout << "global shared value: " << shared_value << "\n";

    return EXIT_SUCCESS;    
}