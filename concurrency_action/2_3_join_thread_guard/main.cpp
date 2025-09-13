#include <iostream>
#include <thread>

class thread_guard {
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_): t(t_) {}
    ~thread_guard() {
        if(t.joinable()) {
            t.join();
        }
    }

    // thread_guard 禁止赋值和拷贝，因为std::thread 也不能拷贝
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

void do_something(int& i) {
    ++i;
}


struct func {
    int& i;

    func(int& i_): i(i_) {}

    void operator()() {
        for(unsigned j=0; j<1000'000; ++j) {
            do_something(i);
        }
    }
};

void do_something_in_current_thread() {

}

void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    // 使用thread_guard类的RAIL 属性简化代码，如果有异常，会在异常退出前调用析构函数
    // 如果没有异常，会在f 结束前调用析构函数
    thread_guard g(t);
    do_something_in_current_thread();
}

int main(int argc, char* argv[]) {
    f();   
    return EXIT_SUCCESS;
}