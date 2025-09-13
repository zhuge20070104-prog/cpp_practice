#include <thread>
#include <iostream>

int main(int argc, char* argv[]) {
    auto lambda_th = []() {
        std::cout << "我的线程开始执行了..." << std::endl;

        std::cout << "我的线程结束执行了..." << std::endl;
    };

    std::thread th(lambda_th);
    th.join();
    std::cout << "Hello world!" << std::endl;
    return EXIT_SUCCESS;
}