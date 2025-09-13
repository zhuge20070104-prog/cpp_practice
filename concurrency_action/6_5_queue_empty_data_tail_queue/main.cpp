#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>
#include <string>
#include <queue>
#include <memory>
#include <exception>
#include <condition_variable>

template <typename T>
class queue {
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    }; 

    std::unique_ptr<node> head;
    node* tail;

public:

    queue(): head(new node), tail(head.get()) {}

    queue(queue const& other) = delete;
    queue& operator=(queue const& other) = delete;


    std::shared_ptr<T> try_pop() {
        if(head.get() == tail) {
            return std::shared_ptr<T>();
        }

        std::shared_ptr<T> const res(head->data);
        std::unique_ptr<node> const old_head = std::move(head);
        head = std::move(old_head->next);
        return res;
    }

    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p (new node);
        tail->data = new_data;
        node* const new_tail = p.get();
        tail->next = std::move(p);
        tail = new_tail;
    }

    bool empty() const {
        return tail == head.get();
    }
};

int main(int argc, char* argv[]) {
    
    queue<int> q;
    for(int i=0; i<10; ++i) {
        q.push(i);
    }

    while(!q.empty()) {
        std::cout << *q.try_pop() << std::endl;
    }
    return EXIT_SUCCESS;
}