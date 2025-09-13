#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>


struct some_resource {
    void do_something() {
        std::cout << "some_resource::do_something()" << std::endl;
    }
};

// 全局的resource_ptr对象，没有就给他来一个，
// 有就不搞了
std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

void foo() {
    std::unique_lock<std::mutex> lk(resource_mutex);
    if(!resource_ptr) {
        resource_ptr.reset(new some_resource);
    }
    lk.unlock();
    resource_ptr->do_something();
}


int main(int argc, char* argv[]) {
    std::vector<std::thread> threads;

    for(int i=0; i<10; ++i) {
        threads.push_back(std::thread([&](){
            foo();
        }));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}