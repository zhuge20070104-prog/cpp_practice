#include "stopwatch11.h"
#include <thread>
#include <vector>
#include <future>
#include <atomic>

typedef unsigned long long counter_t;

bool atomic_test_1() {
    struct foo {
        int i;
        int j;
        int k;
        int l;
    };

    std::atomic<foo> f;
    foo f1 {2, 3, 4, 5};
    f.store(f1);
    foo f2 = f.load();

    return (f2.i == 2 && f2.j == 3 && f2.k == 4 && f2.l == 5 && f.is_lock_free() == false);
}

void f1(int n) {
    std::cout << "thread " << n << std::endl;
}

void thread_example() {
    std::thread t1;
    t1 = std::thread(f1, 1);
    t1.join();

    std::thread t2(f1, 2);
    std::thread t3(std::move(t2));
    std::thread t4([](){
        return;
    });

    t4.detach();
    t3.join();
}

// 使用promise 跨线程返回值
void promise_future_example_1() {
    auto meaning = [](std::promise<int>& prom) {
        prom.set_value(42);
    };

    std::promise<int> prom;
    std::thread(meaning, std::ref(prom)).detach();

    std::future<int> result = prom.get_future();
    std::cout << "the meaning of life: " << result.get() << "\n";
}

// 使用packaged_task 跨线程返回值
void promise_future_example_2() {
    auto meaning = std::packaged_task<int(int)>([](int n) {
        return n;
    });
    auto result = meaning.get_future();
    auto t = std::thread(std::move(meaning), 42);
    std::cout << "the meaning of life: " << result.get() << "\n";
    t.join();
}

// 使用std::async(std::launch::deferred | std::launch::async)，
// 注意，这里由操作系统决定调度策略
void promise_future_example_3() {
    auto meaning = [](int n) {
        return n;
    };
    auto result = std::async(std::move(meaning), 42);
    std::cout << "the meaning of life: " << result.get() << "\n";
}


bool thread_start_stop_test(unsigned long multiplier) {
    std::thread t;
    {
        // 换行join
        StopWatch sw("thread start/stop");
        for(unsigned i=0; i<10* multiplier; ++i) {
            t = std::thread([](){
                return;
            });
            t.join();
        } 
    }

    {
        // 同行join
        StopWatch sw("thread start/stop 2");
        for(unsigned i=0; i<10* multiplier; ++i) {
            std::thread([](){
                return;
            }).join();
        }
    }

    {
        // 同行detach
        StopWatch sw("thread start/detach");
        for(unsigned i=0; i<10* multiplier; ++i) {
            std::thread([](){
                return;
            }).detach();
        }
    }
    return true;
}

bool async_startstop_test(unsigned long multiplier) {
    {
        StopWatch sw("async task start/stop");
        for(unsigned i=0; i<10* multiplier; ++i) {
            std::async(std::launch::async, [](){
                return;
            });
        }
    }

    {
        StopWatch sw("deferred async task start/stop");
        for(unsigned i=0; i<10* multiplier; ++i) {
            std::async(std::launch::deferred, []() {
                return;
            });
        }
    }
    return true;
}

void time_waster(unsigned iterations) {
    unsigned fibonacci(unsigned);
    for(counter_t i=0; i<iterations; ++i) {
        fibonacci(30);
    }
}

// 这个函数故意写的负优化，写的那么慢的
unsigned fibonacci(unsigned i) {
    if(i>2) {
        return fibonacci(i-1) + fibonacci(i-2);
    } else {
        return 1;
    }
}

void multithreaded_timewaster(unsigned iterations, unsigned threads) {
    std::vector<std::thread> t;
    t.reserve(threads);
    for(unsigned i=0; i<threads; ++i) {
        t.push_back(std::thread(time_waster, iterations/threads));
    }

    for(unsigned i=0; i<threads; ++i) {
        t[i].join();
    }
}

bool multi_thread_test(unsigned long multiplier) {
    {
        StopWatch sw("unthreaded test");
        time_waster(multiplier);
    }

    {
        StopWatch sw("1 thread");
        multithreaded_timewaster(multiplier, 1);
    }

    {
        StopWatch sw("2 threads");
        multithreaded_timewaster(multiplier, 2);
    }

    {
        StopWatch sw("3 threads");
        multithreaded_timewaster(multiplier, 3);
    }

    {
        StopWatch sw("4 threads");
        multithreaded_timewaster(multiplier, 4);
    }


    {
        StopWatch sw("5 threads");
        multithreaded_timewaster(multiplier, 5);
    }

    {
        StopWatch sw("10 threads");
        multithreaded_timewaster(multiplier, 10);
    }

    // TODO: 可能需要移除100 和 1000， 机器性能不足
    {
        StopWatch sw("100 threads");
        multithreaded_timewaster(multiplier, 100);
    }

    {
        StopWatch sw("1000 threads");
        multithreaded_timewaster(multiplier, 1000);
    }

    return true;
}

// 通过counter计数，生产者把counter赋值给shared_data,consumer消费shared_data
// 使用主线程通知生产者和消费者退出
void cv_example() {
    std::mutex m;
    std::condition_variable cv;
    bool terminate = false;
    int shared_data = 0;
    int counter = 0;

    auto consumer = [&]() {
        std::unique_lock<std::mutex> lk(m);
        do {
            while(!(terminate || shared_data != 0)) {
                cv.wait(lk);
            }
            if(terminate) {
                break;
            }

            shared_data = 0;
            cv.notify_one();
        } while(true);
    };

    auto producer = [&]() {
        std::unique_lock<std::mutex> lk(m);
        for(counter=1; true; ++counter) {
            cv.wait(lk, [&]() {
                return terminate || shared_data == 0;
            });

            if(terminate) {
                break;
            }
            shared_data = counter;
            cv.notify_one();
        }
    };

    auto p = std::thread(producer);
    auto c = std::thread(consumer);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    {
        std::lock_guard<std::mutex> l(m);
        terminate = true;
    }  
    std::cout << "Total items consumed " << counter << std::endl;
    cv.notify_all();
    p.join();
    c.join();
}

int test_atomic(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    default: return -1;
    case 0: return 4;
    
    case 1: {
        {
            // 验证原子变量特性
            std::atomic<counter_t> x;
            rc &= x.is_lock_free();
            rc &= atomic_test_1();
        }

        {
            // 验证fibonacci 函数的正确性
            rc &= (fibonacci(1) == 1);
            rc &= (fibonacci(2) == 1);
            rc &= (fibonacci(3) == 2);
			rc &= (fibonacci(4) == 3);
			rc &= (fibonacci(5) == 5);
			rc &= (fibonacci(6) == 8);
			rc &= (fibonacci(7) == 13);
			rc &= (fibonacci(40) > 100000000);
        }

        {
            // 线程构建方式
            thread_example();
            // 条件变量用法
            cv_example();
            promise_future_example_1();
            promise_future_example_2();
            promise_future_example_3();
        }
    } 
        break;
    
    case 2: {
        volatile unsigned n = 30;
        {
            // fibonacci(30) < 2 ^ 30
            StopWatch sw("fibonacci test");
            for(counter_t i = 0, iterations = multiplier; i<iterations; ++i) {
                rc &= (fibonacci(n) < (1u << n));
            }
        }
    }
        break;
    
    case 3: {
        {
            // 测试给std::atomic变量赋值的速度
            StopWatch sw("atomic test");
            std::atomic<counter_t> x;
            for(counter_t i=0, iterations = 10'000'000 * multiplier; i<iterations; ++i) {
                x = i;
            }
            rc &= (x != 0);
        }

        {
            // 测试给普通变量赋值的速度
            StopWatch sw("non-atomic test");
            counter_t x;
            for(counter_t i=0, iterations = 10'000'000 * multiplier; i<iterations; ++i) {
                x = i;
            }
            rc &= (x != 0);
        }
    } 
        break;

    case 4: {
        // 各种线程join/detach的速度测试
        rc &= thread_start_stop_test(multiplier);
        // std::async(std::launch::async和std::launch::deferred)速度测试
        rc &= async_startstop_test(multiplier);
        // 多线程计算fibonacci测试
        rc &= multi_thread_test(multiplier);
    } 
        break;
    }

    return (rc) ? 1: 0;
}