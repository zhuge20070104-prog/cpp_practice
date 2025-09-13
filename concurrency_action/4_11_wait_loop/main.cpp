#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <chrono>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;

bool is_done() {
    static int done_idx {0};
    ++done_idx;
    if(done_idx <= 10) {
        return false;
    }
    return true;
}

// 每500毫秒检查一下是否结束，结束就退出
bool wait_loop() {
    // steady_clock 表示单调时钟，只能增加，不能减少
    // steady_clock 与实际时间无关，他一般用来测量时间间隔
    std::unique_lock<std::mutex> lk(m);
    while(!is_done()) {
        auto const timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
        if(cv.wait_until(lk, timeout) == std::cv_status::timeout) {
            std::cout << "continue to wait..." << std::endl;
        }
    }

    return is_done();
}

int main(int argc, char* argv[]) {  
    auto fut = std::async(std::launch::async, wait_loop);
    auto fut1 = std::async(std::launch::async, wait_loop);

    auto res = fut.get();
    auto res1 = fut1.get();
    std::cout << std::boolalpha << "res: " << res 
        << "    res1: " << res1 << "\n";
    return EXIT_SUCCESS;
}