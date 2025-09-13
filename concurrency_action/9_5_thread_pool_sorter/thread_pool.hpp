#ifndef _FREDRIC_THREAD_POOL_HPP_
#define _FREDRIC_THREAD_POOL_HPP_
#include "function_wrapper.hpp"
#include "thread_safe_queue.hpp"
#include "work_stealing_queue.hpp"
#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <utility>
#include <future>
#include <queue>
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


class thread_pool {
    typedef function_wrapper task_type;

    std::atomic<bool> done;
    threadsafe_queue<task_type> pool_work_queue;
    std::vector<std::unique_ptr<work_stealing_queue>> queues;
    join_threads joiner;

    static thread_local work_stealing_queue* local_work_queue;
    static thread_local unsigned my_index;
    static unsigned thread_count;

    void work_thread(unsigned my_index_) {
        my_index = my_index_;
        // 从work_steal_queue列表里面根据索引查找当前的local_work_queue
        local_work_queue = queues[my_index].get();
        while(!done) {
            run_pending_task();
        }
    }

    bool pop_task_from_local_queue(task_type& task) {
        return local_work_queue && local_work_queue->try_pop(task);
    }

    bool pop_task_from_pool_queue(task_type& task) {
        return pool_work_queue.try_pop(task);
    }

    bool pop_task_from_other_thread_queue(task_type& task) {
        for(unsigned i=0; i<queues.size(); ++i) {
            unsigned const index = (my_index + i +1) % queues.size();
            // TODO: 这里有问题，等会再调, 要保证work_stealing_queue vector建完才行
            if(queues.size() == thread_count && (queues[index]->try_steal(task))) {
                return true;
            }
        }

        return false;
    }

public:
    thread_pool():
        done(false) {
        thread_count = std::thread::hardware_concurrency();

        try {
            for(unsigned i=0; i<thread_count; ++i) {
                // 一个线程一个work_stealing_queue队列
                queues.push_back(std::unique_ptr<work_stealing_queue>(new work_stealing_queue));
                joiner.add_thread(std::thread(&thread_pool::work_thread, this, i));
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

        if(local_work_queue) {
            local_work_queue->push(std::move(task));
        } else {
            pool_work_queue.push(std::move(task));
        }
        return res;
    }

    void run_pending_task() {
        task_type task;
        // 优先级，先拿 local_work_queue里面的，
        // 再拿全局的pool_work_queue里面的，[前面两个都是拿队头最新的]
        // 没有的话，再偷取其他队列队尾的 [后面是偷取队尾最旧的]
        if(pop_task_from_local_queue(task) ||
            pop_task_from_pool_queue(task) ||
            pop_task_from_other_thread_queue(task)) {
            task.call();
        }else {
            std::this_thread::yield();
        }
    }
};

thread_local work_stealing_queue* thread_pool::local_work_queue {nullptr};
thread_local unsigned thread_pool::my_index = 0;
unsigned thread_pool::thread_count = 0;
#endif