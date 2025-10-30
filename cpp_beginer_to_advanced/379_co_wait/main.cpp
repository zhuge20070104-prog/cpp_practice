#include <iostream>
#include <coroutine>

struct CoroType {

    struct promise_type {
        CoroType get_return_object() {
            return CoroType(this);
        }

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        void return_void() {}

        void unhandled_exception() noexcept {
           std::rethrow_exception(std::current_exception());
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
    std::cout << "first thing\n";
    co_await std::suspend_always{};

    std::cout << "second thing\n";
    co_await std::suspend_always{};

    std::cout << "third thing\n";
}


int main(int argc, char* argv[]) {
    auto task {do_work()};
    // resume the coroutine, pauses at first co_await statement
    // task.m_handle() is okay as well, these two are the same thing 
    task.m_handle.resume();

    // check if coroutine is done executing
    std::cout << "Coroutine is done: " << task.m_handle.done() << '\n';
    // resume again, pauses at second co_await statement
    task.m_handle.resume();

    // resume again
    task.m_handle.resume();

    std::cout << "Coroutine is done: " << task.m_handle.done() << '\n';

    
    return EXIT_SUCCESS;
}