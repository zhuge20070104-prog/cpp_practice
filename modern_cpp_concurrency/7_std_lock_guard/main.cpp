#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>

int shared_value = 0;
std::mutex  mtx;

// 虽然进了handle exception 
// 但是程序也能自动解锁
void shared_value_increment() {
    std::lock_guard<std::mutex> lock(mtx);
    
    try{
        ++shared_value;
        throw "dangerous... abort";
    }catch(...) {
        std::cout << "handle exception\n";
    }
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