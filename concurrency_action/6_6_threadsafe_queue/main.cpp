#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>
#include <string>
#include <queue>
#include <memory>
#include <exception>

template <typename T>
class threadsafe_queue {
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::mutex tail_mutex;

    std::unique_ptr<node> head;
    node* tail;

    // get_tail
    node* get_tail() {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head() {
        // 先加锁head_mutex，再加锁tail_mutex
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if(head.get() == get_tail()) {
            return nullptr;
        }

        // 解锁 tail_mutex, 但是head_mutex还在
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return std::move(old_head);
    }

public:
    threadsafe_queue():
        head(new node), tail(head.get()) {}
    
    threadsafe_queue(threadsafe_queue const&) = delete;
    threadsafe_queue& operator=(threadsafe_queue const&) = delete;

    std::shared_ptr<T> try_pop() {
        std::unique_ptr<node> old_head = pop_head();
        return old_head? old_head->data: std::shared_ptr<T>(); 
    }

    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        node* const new_tail = p.get();
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        tail->next = std::move(p);
        tail = new_tail;
    }

    // Empty
    bool empty() {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        return (head.get() == get_tail());
    }
};

int main(int argc, char* argv[]) {
    threadsafe_queue<int> q;

    std::thread t1([&]() {
        for(int i=0; i<10; ++i) {
            q.push(i);
        }
    });

    std::thread t2([&]() {
        while(!q.empty()) {
            std::cout << *(q.try_pop()) << std::endl;
        }
    });

    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}