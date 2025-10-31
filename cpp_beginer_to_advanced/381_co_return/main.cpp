#include <iostream>
#include <coroutine>

struct CoroType {

    struct promise_type {
        int m_value {};
        CoroType get_return_object() {
            return CoroType(this);
        }

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        void return_value(int value) {
            m_value = value;
        }

        // void return_void() {}

        void unhandled_exception() noexcept {
           std::rethrow_exception(std::current_exception());
        }

        std::suspend_always yield_value(int value) {
            m_value = value;
            return {};
        }
    };

    CoroType(promise_type* p): 
        m_handle(std::coroutine_handle<promise_type>::from_promise(*p)) {}
    
    ~CoroType() {
        std::cout << "Handle destroyed\n";
        m_handle.destroy();
    }

    std::coroutine_handle<promise_type> m_handle;
};

CoroType do_work() {
    std::cout << "Resume after initial pause\n";
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_return 4;
}


int main(int argc, char* argv[]) {
    // coroutine pauses here - initial pause
    auto task {do_work()};
    // resume the coroutine, pauses at first co_await statement
    // task.m_handle() is okay as well, these two are the same thing 
    task.m_handle.resume();
    std::cout << task.m_handle.promise().m_value << '\n';

    // resume again, pauses at second co_await statement
    task.m_handle.resume();
    std::cout << task.m_handle.promise().m_value << '\n';
    // resume again
    task.m_handle.resume();
    std::cout << task.m_handle.promise().m_value << '\n';

    std::cout << std::boolalpha << task.m_handle.done() << '\n';
    
    task.m_handle.resume();
    std::cout << task.m_handle.promise().m_value << '\n';
    std::cout << std::boolalpha << task.m_handle.done() << '\n';
    
    return EXIT_SUCCESS;
}