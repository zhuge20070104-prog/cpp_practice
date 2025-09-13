#include <iostream>
#include <thread>


int main(int argc, char* argv[]) {

    auto lambda = [](int x) {
        std::cout << "Hello from thread!" << std::endl;
        std::cout << "Argument passed in: " << x << std::endl;
    };

    std::thread t1(lambda, 100);
    t1.join();

    std::cout << "Hello from main thread" << std::endl;
    return EXIT_SUCCESS;    
}