#include <iostream>
#include <mutex>
#include <algorithm>
#include <functional>
#include <thread>
#include <vector>
#include <string>

class some_data {
    std::string b;
    int a{0};
public:

    int get_a() {
        return a;
    }

    void set_a(int a_) {
        a = a_;
    }

    std::string get_b() {
        return b;
    }

    void do_something() {
        ++a;
        b = std::to_string(a);
    }
};

class data_wrapper {
private:
    some_data data;
    std::mutex m;

public:
    template <typename Function>
    void process_data(Function func) {
        // 原意是使用lock_guard保护mutex
        std::lock_guard<std::mutex> l(m);
        func(data);
    }

    void reset() {
        data.set_a(0);
    }
 
    some_data get_data() {
        return data;
    }
};


some_data* unprotected;

void malicious_function(some_data& protected_data) {
    // 数据通过指针暴露出去，不被保护了
    unprotected = &protected_data;
}

void correct_function(some_data& protected_data) {
    protected_data.do_something();
}

data_wrapper x;

void foo() {
    std::vector<std::thread> threads;
    x.process_data(malicious_function);
    for(int i=0; i<100; ++i) {
        threads.push_back(std::thread([&](){
            unprotected->do_something();
        }));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    std::cout << "Foo: " <<  unprotected->get_a() << std::endl;
}

void correct() {
    std::vector<std::thread> threads;
    for(int i=0; i<100; ++i) {
        threads.push_back(std::thread([&](){
            x.process_data(correct_function);
        }));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    std::cout << "Correct: " << x.get_data().get_a() << std::endl;
}

int main(int argc, char* argv[]) {
    foo();
    x.reset();
    correct();
    return EXIT_SUCCESS;
}