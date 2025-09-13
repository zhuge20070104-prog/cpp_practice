#include <thread>
#include <iostream>

struct ThreadObj {
    void operator()() {
        std::cout << "我的线程开始运行..." << std::endl;

        std::cout << "我的线程结束运行..." << std::endl;
    }
};


int main(int argc, char* argv[]) {
    ThreadObj to;
    std::thread th(to);
    th.join();

    std::cout << "Hello world" << std::endl;
    return EXIT_SUCCESS;
}