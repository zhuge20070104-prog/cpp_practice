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
    while(true) {
        std::future_status status = result.wait_for(std::chrono::milliseconds(0));
        if(status == std::future_status::ready) {
            std::cout << "线程执行成功，返回\n";
            std::cout << "result = " << result.get() << "\n";
            break;
        } else if(status == std::future_status::timeout) {
            std::cout << "超时线程还没执行完\n";
        } else if(status == std::future_status::deferred){
            std::cout << "线程被延时，在主线程中执行\n";
            std::cout << "result = " << result.get() << "\n";
            break;
        }
    }
    return EXIT_SUCCESS;
}