#include <iostream>
#include <thread>

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
    
    try {
        do_something_in_current_thread();
    }catch(...) {
        // 有异常时，不能往后走了，再这里join，重新抛出异常
        t.join();
        throw;
    }
    // 无异常时，在外面join
    t.join();
}

int main(int argc, char* argv[]) {
    f();   
    return EXIT_SUCCESS;
}