#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <list>
#include <utility>
#include <shared_mutex>
#include <map>
#include <vector>
#include <functional>
#include <memory>


template <typename T>
class threadsafe_list {
    struct node {
        std::mutex m;
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;

        node():next() {}

        node(T const& value):
            data(std::make_shared<T>(value)) {}
    };

    node head;

public:
    threadsafe_list() {}

    ~threadsafe_list() {
        // 每个元素 都删除掉
        remove_if([](T const&) {
            return true;
        });
    }

    threadsafe_list(threadsafe_list const&) = delete;
    threadsafe_list& operator=(threadsafe_list const&) = delete;

    // head 里面是空的指针值，head里面是没有值的
    T push_front(T const& value) {
        std::unique_ptr<node> new_node(new node(value));
        std::lock_guard<std::mutex> lk(head.m);
        new_node->next = std::move(head.next);
        head.next = std::move(new_node);
    }

    template <typename Function>
    void for_each(Function f) {
        node* current = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while(node* const next = current->next.get()) {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            f(*next->data);
            current = next;
            lk = std::move(next_lk);
        }
    }

    template <typename Predicate>
    std::shared_ptr<T> find_first_if(Predicate p) {
        node* current = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while(node* const next = current->next.get()) {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            if(p(*next->data)) {
                return next->data;
            }
            current = next;
            lk = std::move(next_lk);
        }
        return std::shared_ptr<T>();
    }

    template <typename Predicate>
    void remove_if(Predicate p) {
        node* current = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while(node* const next = current->next.get()) {
            std::unique_lock<std::mutex> next_lk(next->m);
            if(p(*next->data)) {
                // old_next 这一句是为了释放下一个节点
                std::unique_ptr<node> old_next = std::move(current->next);
                current->next = std::move(next->next);
                next_lk.unlock();
            } else {
                lk.unlock();
                current = next;
                lk = std::move(next_lk);
            }
        }
    }
};

int main(int argc, char* argv[]) {
    threadsafe_list<int> ls;
    std::thread t1([&]() {
        for(int i=0; i<10; ++i) {
            ls.push_front(i);
        }
    });

    std::thread t2([&]() {
        ls.for_each([](int const& ele) {
            std::cout << ele << std::endl;
        });
    });

    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}