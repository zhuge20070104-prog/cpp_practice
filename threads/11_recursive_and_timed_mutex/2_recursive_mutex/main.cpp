#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <future>

std::recursive_mutex mtx;

void test_func2() {
    std::lock_guard<std::recursive_mutex> lock(mtx);
    std::cout << "test_func2() recusive mutex can work here..." << std::endl;
}

void test_func1() {
    std::lock_guard<std::recursive_mutex> lock(mtx);
    std::cout << "test_func1() alright..." << std::endl;
    test_func2();
}

int main(int argc, char* argv[]) {
    std::thread t1(test_func1);
    std::thread t2(test_func2);

    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}