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

void thread_func2(std::shared_future<int>& fut_s) {
    std::cout << "thread_func2() start thread id = " << std::this_thread::get_id() << "\n";
    int res = fut_s.get();  // std::shared_future, 可以多次get
    printf("thread_func2() result = %d\n", fut_s.get()); 
    std::cout << "thread_func2() end thread id = " << std::this_thread::get_id() << "\n";
}

int main(int argc, char* argv[]) {
    std::cout << "main " << " thread id = " << std::this_thread::get_id() << std::endl;
    int var = 7;
    std::future<int> result = std::async(thread_func, var);
    std::shared_future<int> fut_s = result.share();
    // std::shared_future，可以多次get
    printf("main result = %d\n", fut_s.get());
    std::thread t(thread_func2, std::ref(fut_s));
    t.join();
    return EXIT_SUCCESS;
}