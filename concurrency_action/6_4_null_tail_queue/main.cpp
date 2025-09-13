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
        T data;
        std::unique_ptr<node> next;

        node(T data_): data(std::move(data_)) {}
    }; 

    std::unique_ptr<node> head;
    node* tail;

public:

    queue(): tail(nullptr) {}

    queue(queue const& other) = delete;
    queue& operator=(queue const& other) = delete;


    std::shared_ptr<T> try_pop() {
        if(!head) {
            return std::shared_ptr<T>();
        }

        std::shared_ptr<T> const res (
            std::make_shared<T>(std::move(head->data))
        );

        std::unique_ptr<node> const old_head  = std::move(head);
        head = std::move(old_head->next);
        if(!head) {
            tail = nullptr;
        }
        return res;
    }

    void push(T new_value) {
        std::unique_ptr<node> p (new node(std::move(new_value)));
        node* const new_tail = p.get();
        if(tail) {
            tail->next  = std::move(p);
        } else {
            head = std::move(p);
        }
        tail = new_tail;
    }

    bool empty() const {
        return tail == nullptr;
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