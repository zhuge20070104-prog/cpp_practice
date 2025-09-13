#ifndef _FREDRIC_THREAD_POOL_HPP_
#define _FREDRIC_THREAD_POOL_HPP_
#include "thread_safe_queue.hpp"
#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <utility>
#include <future>
#include <utility>
#include <functional>
#include <memory>

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


class function_wrapper {
    struct impl_base {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };

    template <typename F>
    struct impl_type: impl_base {
        F f;
        impl_type(F&& f_): f(std::move(f_)) {}

        void call() {
            f();
        }
    };
    
    std::unique_ptr<impl_base> impl;

public:
    function_wrapper() {}

    // 这个wrapper wrapper的是 packaged_task
    template <typename F>
    function_wrapper(F&& f):
        impl(new impl_type<F>(std::move(f))) {}

    void call() {
        impl->call();
    }

    function_wrapper(function_wrapper&& other): impl(std::move(other.impl)) {}

    function_wrapper& operator=(function_wrapper&& other) {
        impl = std::move(other.impl);
        return *this;
    }

    function_wrapper(function_wrapper const&) = delete;
    function_wrapper(function_wrapper&) = delete;
    function_wrapper& operator=(function_wrapper const&) = delete;
};

class thread_pool {
    std::atomic<bool> done;
    threadsafe_queue<function_wrapper> work_queue;
    join_threads joiner;

    void work_thread() {
        while(!done) {
           function_wrapper task;
            if(work_queue.try_pop(task)) {
                task.call();
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
        done = true;
    }

    template <typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f) {
        typedef typename std::result_of<FunctionType()>::type result_type;
        std::packaged_task<result_type()> task(std::move(f));
        std::future<result_type> res = task.get_future();
        work_queue.push(std::move(task));
        return res;
    }
};
#endif