#include <iostream>
#include <thread>

void test(int x) {
    std::cout << "Hello from thread!" << std::endl;
    std::cout << "Argument passed in: " << x << std::endl;
}

int main(int argc, char* argv[]) {
    std::thread t1(&test, 100);
    t1.join();

    std::cout << "Hello from main thread" << std::endl;
    return EXIT_SUCCESS;    
}