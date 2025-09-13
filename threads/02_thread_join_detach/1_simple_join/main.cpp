#include <thread>
#include <iostream>
#include <future>

void my_print() {
    std::cout << "我的线程开始运行..." << std::endl;
    std::cout << "我的线程运行完毕..." << std::endl;
}

int main(int argc, char* argv[]) {
    std::thread my_thread(my_print);
    my_thread.join();

    if(my_thread.joinable()) {
        std::cout << "可以调用join或者 detach..." << std::endl; 
    } else {
        std::cout << "不能调用join或者 detach..." << std::endl;
    }

    std::cout << "Hello world" << std::endl;
    return EXIT_SUCCESS;
}
