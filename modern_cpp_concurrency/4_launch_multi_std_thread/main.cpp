#include <iostream>
#include <thread>
#include <vector>
#include <functional>


int main(int argc, char* argv[]) {

    auto lambda = [](int x) {
        std::cout << "Hello from thread: " << std::this_thread::get_id() << std::endl;
        std::cout << "Arguments passed in: " << x << std::endl;
    };

    std::vector<std::thread> threads;
    int thread_size = std::thread::hardware_concurrency();
    thread_size = thread_size? thread_size: 2;
    for(int i=0; i<thread_size; ++i) {
        threads.push_back(std::thread(lambda, i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    
    std::cout << "Hello from main thread" << std::endl;
    return EXIT_SUCCESS;    
}