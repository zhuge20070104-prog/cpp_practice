#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <future>


int main(int argc, char* argv[]) {
    std::packaged_task<int(int)> pt([](int var) {
        std::cout << "var = " << var << std::endl;
        std::cout << "lambda thread_func() start " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "lambda thread_func() end " << std::this_thread::get_id() << std::endl;
        return 15;
    });

    std::future<int> result = pt.get_future();
    std::thread t(std::move(pt), 2);
    t.join();
    std::cout << "Result: " << result.get() << std::endl;
    
    return EXIT_SUCCESS;
}