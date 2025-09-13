#include <iostream>
#include <mutex>
#include <algorithm>
#include <functional>
#include <thread>
#include <stack>
#include <memory>
#include <exception>

struct empty_stack: public std::exception {
    char const* what() const noexcept {
        return "empty stack";
    }
};

template <typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack() {}
    threadsafe_stack(threadsafe_stack const& other) {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    // 不允许拷贝赋值
    threadsafe_stack& operator=(threadsafe_stack const&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    } 

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) {
            throw empty_stack();
        }

        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) {
            throw empty_stack();
        }

        value = data.top();
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};


int main(int argc, char* argv[]) {
    threadsafe_stack<int> si;
    std::thread add_thread([&]() {
        for(int i=0; i<10000; ++i) {
            si.push(i);
        }
    });
    
    std::thread pop_thread([&]() {
        for(int i=0; i<10000; ++i) {
            if(!si.empty()) {
                std::cout << *(si.pop()) << std::endl;
            }
        }
    });

    add_thread.join();
    pop_thread.join();

    return EXIT_SUCCESS;
}