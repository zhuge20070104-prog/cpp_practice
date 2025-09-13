#include <iostream>
#include <mutex>
#include <thread>
#include <stdexcept>
#include <chrono>

class hierarchical_mutex {
    std::mutex internal_mutex;
    int level;
    int previous_level;
    // A thread local variable is a global variable in the current thread
    static thread_local int thread_level;

    // 检查是否有更高优先级的互斥锁已经被在当前线程中锁定了
    void is_lock_valid() {
        if(thread_level >= level) {
            throw std::runtime_error("High level mutex has already locked");
        }
    }

    //  当锁定一个mutex时，要做两件事，a) 更新当前线程的mutex的全局值，thread_level
    // b) 保存上一个值到previous_level，以便当前mutex解锁时，level可以回到上一个值
    void update_levels() {
        previous_level = thread_level;
        thread_level = level;
    }

public:
    explicit hierarchical_mutex(int level_) {
        level = level_;
        previous_level = 0;
    }

    void lock() {
        is_lock_valid();
        internal_mutex.lock();
        update_levels();
    }

    void unlock() {
        thread_level = previous_level;
        internal_mutex.unlock();
    }

    bool try_lock() {
        is_lock_valid();
        if(!internal_mutex.try_lock()) {
            return false;
        }

        update_levels();
        return true;
    } 
};

thread_local int  hierarchical_mutex::thread_level = 0;

hierarchical_mutex mutex_a(1000);
hierarchical_mutex mutex_b(10000);

void do_something_with_mutex_a() {
    std::lock_guard<hierarchical_mutex> lock_a(mutex_a);
}

void do_something_with_mutex_b() {
    std::lock_guard<hierarchical_mutex> lock_b(mutex_b);
}

void do_something() {
    std::lock_guard<hierarchical_mutex> lock_a(mutex_a);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    do_something_with_mutex_b();
}

void do_something_else() {
    std::lock_guard<hierarchical_mutex> lock_b(mutex_b);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    do_something_with_mutex_a();
}

// 代码将会throw exception, 因为有死锁存在，
// 需要重新设计代码
int main(int argc, char* argv[]) {
    std::thread t1(do_something);
    std::thread t2(do_something_else);
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}