#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <future>

class X {
public:
    int thread_func(int var) {
        std::cout << "var = " << var << std::endl;
        std::cout << "X::thread_func() start " << " thread id = " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20000));
        std::cout << "X::thread_func() end " << " thread id = " << std::this_thread::get_id() << std::endl;        
        return 5;
    }
};

int main(int argc, char* argv[]) {
    std::cout << "main " << " thread id = " << std::this_thread::get_id() << std::endl;
    X x;
    int var = 7;
    std::future<int> result = std::async(&X::thread_func, &x, var);
    std::cout << "Continue..." << std::endl;
    // 流程卡在这里等待线程执行结束
    std::cout << result.get() << std::endl;  
    std::cout << "Main 主函数执行结束!" << std::endl;
    return EXIT_SUCCESS;
}