#ifndef _FREDRIC_THREADSAFE_STACK_HPP_
#define _FREDRIC_THREADSAFE_STACK_HPP_
#include <iostream>
#include <mutex>
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
            return std::shared_ptr<T>();
        }

        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) {
            return;
        }
        value = std::move(data.top());
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};
#endif 