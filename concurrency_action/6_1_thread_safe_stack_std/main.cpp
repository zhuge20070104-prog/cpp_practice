#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>
#include <string>
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

    threadsafe_stack& operator=(threadsafe_stack const&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) {
            throw empty_stack();
        }

        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) {
            throw empty_stack();
        }
        value = std::move(data.top());
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

int main(int argc, char* argv[]) {
    threadsafe_stack<int> s;
    std::thread t1([&]() {
        for(int i=0; i<10; ++i) {
            s.push(i);
        }
    });
    std::thread t2([&]() {
        for(int i=10; i<20; ++i) {
            s.push(i);
        }
    });

    std::thread t3([&]() {
        while(!s.empty()) {
            std::cout << *(s.pop()) << std::endl;
        }
    });

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}