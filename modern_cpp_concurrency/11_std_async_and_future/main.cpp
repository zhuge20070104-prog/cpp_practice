#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>
#include <memory>

int square(int x) {
    return x * x;
}

int main(int argc, char* argv[]) {
    std::future<int> fut = std::async(&square, 12);
    auto result = fut.get();
    std::cout << "result is: " << result << std::endl;
    return EXIT_SUCCESS;    
}