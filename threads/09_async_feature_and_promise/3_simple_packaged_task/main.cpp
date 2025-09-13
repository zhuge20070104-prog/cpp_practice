#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <future>

int thread_func(int var) {
    std::cout << "var = " << var << std::endl;
    std::cout << "thread func() start " << "thread id = " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "thread func() end " << "thread id = " << std::this_thread::get_id() << std::endl;
    return 5;
}

int main(int argc, char* argv[]) {
    std::cout << "main " << " thread id = " << std::this_thread::get_id() << std::endl;
    std::packaged_task<int(int)> pt(thread_func);
    std::thread t(std::ref(pt), 1);
    t.join();
    std::future<int> result = pt.get_future();
    std::cout << result.get() << std::endl;
    return EXIT_SUCCESS;
}