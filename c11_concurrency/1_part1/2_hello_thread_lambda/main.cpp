#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    // 使用lambda 表达式做线程函数
    std::thread th([](){
        std::cout << "Hello from thread!\n";
    });
    std::cout << "Hi from main!\n";
    th.join();
    return EXIT_SUCCESS;
}