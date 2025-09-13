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
    // 从std::packaged_task直接构造std::shared_future
    std::packaged_task<int(int)> pt(thread_func);
    // 直接根据packaged_task， 构建shared_future
    std::shared_future<int> fut_s(pt.get_future());
    std::thread t(std::move(pt), 7);

    std::cout << "Main get shared future: " << fut_s.get() << std::endl;

    std::thread t2(thread_func2, std::ref(fut_s));
    t.join();
    t2.join();

    std::cout << "Main end." << std::endl;
    return EXIT_SUCCESS;
}