#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>
#include <memory>


int main(int argc, char* argv[]) {
    std::mutex mtx;
    std::condition_variable cv;
    int result = 0;
    bool notified = false;

    std::thread reporter([&]() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&](){
            return notified;
        });

        std::cout << "Reporter, result is: " << result << std::endl;
    });

    std::thread worker([&]() {
        std::lock_guard<std::mutex> lock(mtx);
        result = 42 + 1 + 7;
        notified = true;
        cv.notify_one();
    });

    reporter.join();
    worker.join();
    return EXIT_SUCCESS;    
}