#include <regex>
#include <iostream>

#include <thread>
#include <future>
#include <chrono>

class X {
public:
    void set_trajectory(int const& obj) {
        std::cout << "Thread1: value = " << obj << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    }
};

std::future<void> res;

int main(int argc, char* argv[]) {
    X x;
    int val = 3;
   
    res = std::async(std::launch::async, &X::set_trajectory, &x, std::cref(val));
    std::cout << "Main thread 1 --> " << std::this_thread::get_id() << std::endl;    
    res.get();

    int val2 = 5;
    res = std::async(std::launch::async, &X::set_trajectory, &x, std::cref(val2));
    std::cout << "Main thread 2 --> " << std::this_thread::get_id() << std::endl;   
    res.get();
    return EXIT_SUCCESS;
}