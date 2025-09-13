#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>
#include <string>

// release -> consume对的意义
// consume 是说，如果依赖于指针等间接依赖，这些间接依赖能保证内存顺序的一致性
// 就是说不会互换 代码看到的语句顺序
// 事实上现代编译器中，release -> consume被实现为release -> acquire对

struct X {
    int i;
    std::string s;
};

std::atomic<X*> p;
std::atomic<int> a;

void create_x() {
    X* x = new X;
    x->i = 42;
    x->s = "Hello";
    a.store(99, std::memory_order_relaxed);
    p.store(x, std::memory_order_release);
}

void use_x() {
    X* x;
    // consume 这里其实内部是acquire 实现
    while(!(x =p.load(std::memory_order_consume))) {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
    assert(x->i == 42);
    assert(x->s == "Hello");
    assert(a.load(std::memory_order_relaxed) == 99);
}


int main(int argc, char* argv[]) {
    std::thread t1(create_x);
    std::thread t2(use_x);
 
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}