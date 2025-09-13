#include <iostream>
#include <mutex>
#include <thread>

struct some_big_object {
    int x;
};

void swap(some_big_object& lhs, some_big_object& rhs) {
    std::swap(lhs.x, rhs.x);
}

class X {
private:
    some_big_object& some_detail;
    mutable std::mutex m;
public:
    X(some_big_object & sd): some_detail(sd) {
    }

    // 同时锁住两个std::mutex，来交换 some_detail的值
    friend void swap(X& lhs, X& rhs) {
        if(&lhs == &rhs) {
            return;
        }

        std::lock(lhs.m, rhs.m);
        std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
        swap(lhs.some_detail, rhs.some_detail);
    }
};

int main(int argc, char* argv[]) {
    some_big_object sd1{8};
    some_big_object sd2{9};
    X x1(sd1);
    X x2(sd2);

    std::thread t1([&]() {
        for(int i=0; i<3; ++i) {
            swap(x1, x2);
        }
    });

    std::thread t2([&]() {
        for(int i=0; i<5; ++i) {
            swap(x1, x2);
        }
    });

    t1.join();
    t2.join();

    std::cout << "sd1.x: " << sd1.x << std::endl;
    std::cout << "sd2.x: " << sd2.x << std::endl;

    return EXIT_SUCCESS;
}