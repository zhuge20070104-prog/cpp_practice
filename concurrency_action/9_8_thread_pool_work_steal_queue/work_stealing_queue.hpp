#ifndef _FREDRIC_WORK_STEAL_QUEUE_HPP_
#define _FREDRIC_WORK_STEAL_QUEUE_HPP_
#include "function_wrapper.hpp"
#include <deque>
#include <mutex>


// 简单的双端队列的 线程安全的版本
// 注意try_pop 是从头部走，搞最新的task
// try_steal是从尾部走，搞最老的task
class work_stealing_queue {
private:
    typedef function_wrapper data_type;
    std::deque<data_type> the_queue;
    mutable std::mutex the_mutex;

public:
    work_stealing_queue() {}
    work_stealing_queue(work_stealing_queue const&) = delete;
    work_stealing_queue& operator=(work_stealing_queue const&) = delete;

    void push(data_type data) {
        std::lock_guard<std::mutex> lock(the_mutex);
        the_queue.push_front(std::move(data));
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(the_mutex);
        return the_queue.empty();
    }

    bool try_pop(data_type& res) {
        std::lock_guard<std::mutex> lock(the_mutex);
        if(the_queue.empty()) {
            return false;
        }

        res = std::move(the_queue.front());
        the_queue.pop_front();
        return true;
    }

    bool try_steal(data_type& res) {
        std::lock_guard<std::mutex> lock(the_mutex);
        if(the_queue.empty()) {
            return false;
        }
        res = std::move(the_queue.back());
        the_queue.pop_back();
        return true;
    }


};
#endif