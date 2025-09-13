#include "thread_safe_queue.hpp"
#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <utility>
#include <iostream>


struct join_threads {

    std::thread& operator[](int index) {
        return threads[index];
    }

    void add_thread(std::thread&& thread) {
        threads.emplace_back(std::move(thread));
    }

    ~join_threads() {
        for(std::thread& thread: threads) {
            if(thread.joinable()) {
                thread.join();
            }
        }
    }
private:
    std::vector<std::thread> threads;
};

class thread_pool {
    std::atomic<bool> done;
    threadsafe_queue<std::function<void()>> work_queue;
    join_threads joiner;

    void work_thread() {
        while(!done) {
            std::function<void()> task;
            if(work_queue.try_pop(task)) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }

public:
    thread_pool():
        done(false) {
        unsigned const thread_count = std::thread::hardware_concurrency();

        try {
            for(unsigned i=0; i<thread_count; ++i) {
                joiner.add_thread(std::thread(&thread_pool::work_thread, this));
            }
        } catch(...) {
            done = true;
            throw;
        }
    }

    ~thread_pool() {
        // 不能在这done，你不知道他跑完了没有
        // done = true;
    }

    template <typename FunctionType>
    void submit(FunctionType f) {
        work_queue.push(std::function<void()>(f));
    }
};


int main(int argc, char* argv[]) {
    thread_pool pool;
    for(int i=0; i<10; ++i) {
        pool.submit([i]() {
            std::cout << "Print: " << i << std::endl;
        });
    }
    return EXIT_SUCCESS;
}