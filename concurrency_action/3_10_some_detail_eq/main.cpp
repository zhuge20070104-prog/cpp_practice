#include <iostream>
#include <mutex>
#include <thread>


class Y {
private:
    int some_detail;
    mutable std::mutex m;
    
    int get_detail() const {
        std::lock_guard<std::mutex> lock_a(m);
        return some_detail;
    }

public:
    Y(int sd): some_detail(sd) {
    }

    friend bool operator == (Y const& lhs, Y const& rhs) {
        if(&lhs == &rhs) {
            return true;
        }

        // 不存在死锁了，当lhs走出get_detail函数的时候， lhs_a被解锁
        // 当rhs走出get_detail函数的时候， rhs_a被解锁。
        // 然后 lhs可以获得rhs的锁
        // rhs也可以获得lhs的锁
        // 所以死锁问题解决了。
        int const lhs_value = lhs.get_detail();
        int const rhs_value = rhs.get_detail();
        return lhs_value == rhs_value;
    }
};

int main(int argc, char* argv[]) {
    Y lhs(3);
    Y rhs(5);
    std::thread t1 ([&]() {
        for(int i=0; i<10; ++i) {
            if(lhs == rhs) {
                std::cout << "lhs == rhs" << std::endl;
            } else {
                std::cout << "lhs != rhs" << std::endl;
            }
        }
    });
    std::thread t2 ([&]() {
        for(int i=0; i<10; ++i) {
            if(rhs == lhs) {
                std::cout << "rhs == lhs" << std::endl;
            } else {
                std::cout << "rhs != lhs" << std::endl;
            }
        }
    });
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}