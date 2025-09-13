#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <future>

int thread_func(int var) {
    std::cout << "thread_func(int var) start " << "thread id = " << std::this_thread::get_id() << std::endl;
    std::cout << "var = " << var << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "thread_func(int var) end " << "thread id = " << std::this_thread::get_id() << std::endl;
    return 5;
}


int main(int argc, char* argv[]) {
    std::cout << "main " << " thread id = " << std::this_thread::get_id() << std::endl;
    int var = 7;
    std::future<int> result = std::async(thread_func, var);
    // 流程卡在这里等待线程执行结束
    std::cout << result.get() << std::endl;  
    return EXIT_SUCCESS;
}