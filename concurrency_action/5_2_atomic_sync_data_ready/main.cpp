#include <iostream>
#include <atomic>
#include <mutex>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <chrono>

std::vector<int> data;
std::atomic<bool> data_ready(false);

void read_thread() {
    while(!data_ready.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "The answer = " << data[0] << "\n";
}

void writer_thread() {
    data.push_back(42);
    data_ready = true;
}

int main(int argc, char* argv[]) {  

    std::thread w_thread(writer_thread);
    std::thread r_thread(read_thread);

    w_thread.join();
    r_thread.join();
    return EXIT_SUCCESS;
}