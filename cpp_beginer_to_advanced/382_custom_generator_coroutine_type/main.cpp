#include <iostream>
#include <coroutine>
#include <cassert>

template<typename T>
struct Generator {

    struct promise_type {
        T m_value {};
        Generator get_return_object() {
            return Generator(this);
        }

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        void return_void() {
            std::cout << "co_return void called\n";
        }

        void unhandled_exception() noexcept {
           std::rethrow_exception(std::current_exception());
        }

        std::suspend_always yield_value(T value) {
            m_value = value;
            return {};
        }
    };

    Generator(promise_type* p): 
        m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
    
    ~Generator() {
        std::cout << "Handle destroyed\n";
        m_handle.destroy();
    }

    T operator()() {
        assert(m_handle != nullptr);
        m_handle.resume();
        return m_handle.promise().m_value;
    }

    std::coroutine_handle<promise_type> m_handle;
};

Generator<int> do_work() {
    std::cout << "Resume after initial pause\n";
    co_yield 1;
    co_yield 2;
    co_yield 3;
}

Generator<int> infinite_number_stream(int start) {
    auto value {start};
    std::cout << "Infinite number stream: \n";
    for(int i{0};;++i) {
        co_yield value;
        ++value;
    }
}

Generator<int> range(int first, int last) {
    std::cout << "range sequence: \n";
    while(first != last) {
        co_yield first++;
    }
}


int main(int argc, char* argv[]) {
   
    auto task_generator {do_work()};
    std::cout << task_generator() << '\n';
    std::cout << task_generator() << '\n';
    std::cout << task_generator() << '\n';
    std::cout << task_generator() << '\n';
    std::cout << std::boolalpha << task_generator.m_handle.done() << '\n';

    auto task_infinite_sequence {infinite_number_stream(1)};
    for(unsigned int i{0}; i<10; ++i) {
        std::cout << task_infinite_sequence() << '\n';
    }

    auto task_range_sequence {range(20, 80)};

    for(unsigned int i{0}; i<30; ++i) {
        std::cout << task_range_sequence() << '\n';
    }

    return EXIT_SUCCESS;
}