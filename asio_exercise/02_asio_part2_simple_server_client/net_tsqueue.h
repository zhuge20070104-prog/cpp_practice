#ifndef _FREDRIC_NET_TS_QUEUE_H_
#define _FREDRIC_NET_TS_QUEUE_H_

#include "net_common.h"

namespace olc {
namespace net {
    template <typename T>
    class ts_queue {
    public:
        ts_queue() = default;
        ts_queue(ts_queue<T> const&) = delete;
        virtual ~ts_queue() {
            clear();
        }
    public:
        T const& front() {
            std::scoped_lock lock(mux_queue);
            return deq_queue.front();
        }

        T const& back() {
            std::scoped_lock lock(mux_queue);
            return deq_queue.back();
        }

        T pop_front() {
            std::scoped_lock lock(mux_queue);
            auto t = std::move(deq_queue.front());
            deq_queue.pop_front();
            return t;
        }

        T pop_back() {
            std::scoped_lock lock(mux_queue);
            auto t = std::move(deq_queue.back());
            deq_queue.pop_back();
            return t;
        }

        void push_back(T const& item) {
            std::scoped_lock lock(mux_queue);
            deq_queue.emplace_back(std::move(item));

            std::unique_lock<std::mutex> u_lock(mux_blocking);
            cv_blocking.notify_one();
        }

        void push_front(T const& item) {
            std::scoped_lock lock(mux_queue);
            deq_queue.emplace_front(std::move(item));

            std::unique_lock<std::mutex> u_lock(mux_blocking);
            cv_blocking.notify_one();
        }

        bool empty() {
            std::scoped_lock lock(mux_queue);
            return deq_queue.empty();
        }

        std::size_t count() {
            std::scoped_lock lock(mux_queue);
            return deq_queue.size();
        }


        void clear() {
            std::scoped_lock lock(mux_queue);
            deq_queue.clear();
        }

        void wait() {
            while(empty()) {
                std::unique_lock<std::mutex> u_lock(mux_blocking);
                cv_blocking.wait(u_lock);
            }
        }
    protected:
        std::mutex mux_queue;
        std::deque<T> deq_queue;
        std::condition_variable cv_blocking;
        std::mutex mux_blocking;
    };
}
}
#endif