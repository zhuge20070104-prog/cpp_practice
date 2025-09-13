#include <thread>
#include <vector>
#include <iostream>

void test_thread() {
    std::cout << "我是线程: " << std::this_thread::get_id() << std::endl;
    std::cout << "线程: " << std::this_thread::get_id() << "执行结束" << std::endl;
}

int main(int argc, char* argv[]) {
    std::vector<std::thread> threads;

    for(std::size_t i=0; i<10; ++i) {
        threads.emplace_back(test_thread);
    }

    for(std::size_t i=0; i<10; ++i) {
        threads[i].join();
    }
    return EXIT_SUCCESS;
}