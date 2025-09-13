#include <iostream>
#include <atomic>
#include <mutex>
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>


class spinlock_mutex {
    std::atomic_flag flag;

public:
    spinlock_mutex():
        flag(ATOMIC_FLAG_INIT) {}
    
    void lock() {
        while(flag.test_and_set(std::memory_order_acquire));
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

static int i{0};
spinlock_mutex mtx;

void update_i() {
    std::lock_guard<spinlock_mutex> lock(mtx);
    for(int idx=0; idx<10; ++idx) {
        ++i;
    }
}


int main(int argc, char* argv[]) {  
    std::vector<std::thread> threads;

    for(int idx=0; idx<10; ++idx) {
        threads.push_back(std::thread(update_i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    std::cout << "Final i: " << i << "\n";

    return EXIT_SUCCESS;
}