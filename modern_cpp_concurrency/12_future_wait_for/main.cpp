#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>
#include <memory>


bool buffered_file_loader() {
    std::size_t bytes_loaded = 0;
    while (bytes_loaded < 20000) {
        std::cout << "thread: loading file..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bytes_loaded += 1000;
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::future<bool> back_ground_fut = std::async(std::launch::async, &buffered_file_loader);
    std::future_status status;
    while (true) {
        std::cout << "Main thread is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        status = back_ground_fut.wait_for(std::chrono::milliseconds(1));
        if(status == std::future_status::ready) {
            std::cout << "our data is ready ... " << std::endl;
            break;
        }
    }
    
    return EXIT_SUCCESS;    
}