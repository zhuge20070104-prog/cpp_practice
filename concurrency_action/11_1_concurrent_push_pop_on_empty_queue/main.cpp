#include "thread_safe_queue.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <future>
#include <cassert>


void test_concurrent_push_and_pop_on_empty_queue() {
    threadsafe_queue<int> q;
    std::promise<void> go, push_ready, pop_ready;
    // 两个async线程都等这个ready，再开始，相当于同时开始，同步
    std::shared_future<void> ready(go.get_future());
    std::future<void> push_done;
    std::future<int> pop_done;

    try {
        push_done = std::async(std::launch::async, 
            [&q, ready, &push_ready]() {
                push_ready.set_value();
                // 等待外面go发指令开始
                ready.wait();
                q.push(42);
            });
        
        pop_done = std::async(std::launch::async, 
            [&q, ready, &pop_ready]() {
                pop_ready.set_value();
                // 等待外面go发指令开始
                ready.wait();
                return *q.wait_and_pop();
            });
        
        push_ready.get_future().wait();
        pop_ready.get_future().wait();
        go.set_value();

        push_done.get();
        assert(pop_done.get() == 42);
        assert(q.empty());
    } catch(...) {
        go.set_value();
        throw;
    }
}


int main(int argc, char* argv[]) {
    test_concurrent_push_and_pop_on_empty_queue();
    return EXIT_SUCCESS;
}