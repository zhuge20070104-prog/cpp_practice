#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> g_count = 0;

void increment() {
    for(int i=0; i<10'000'000; ++i) {
        g_count ++;
    }
}

int main(int argc, char* argv[]) {
    std::thread t(increment);
    std::thread t1(increment);

    t.join();
    t1.join();

    std::cout << "g_count: " << g_count << std::endl;
    
    return EXIT_SUCCESS;
}