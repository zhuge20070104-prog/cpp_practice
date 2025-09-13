#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <vector>

// fence的作用是保证fence之前的所有 代码都完成
// fence的详细文档: https://en.cppreference.com/w/cpp/atomic/atomic_thread_fence
// 这种属于fence atomic synchronization
/**
 * Fence-atomic synchronization
     A release fence F in thread A synchronizes-with atomic acquire operation Y in thread B, if

    a) there exists an atomic store X (with any memory order),
    b) Y reads the value written by X (or the value would be written by release sequence headed by X if X were a release operation),
    c) F is sequenced-before X in thread A.
    In this case, all non-atomic and relaxed atomic stores that are sequenced-before 
        F in thread A will happen-before all non-atomic and relaxed atomic loads from the same locations made in thread B
        after Y.
*/

bool x = false;
std::atomic<bool>  y;
std::atomic<int> z;

void write_x_then_y() {
    x = true;

    // 这是F,他是在y store[X操作]之前的
    std::atomic_thread_fence(std::memory_order_release);
    // 这是 X 操作
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
    // 这是Y操作，Reads the value written by X
    while(!y.load(std::memory_order_relaxed));
    // 这是第二个F
    std::atomic_thread_fence(std::memory_order_acquire);

    // 所有之前的松散原子操作 和非原子操作，都需要在栅栏前完成
    // 这里肯定是 true
    if(x) {
        ++z;
    }
}

int main(int argc, char* argv[]) {
    x = false;
    y = false;
    z = 0;

    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();

    assert(z.load() != 0);
    return EXIT_SUCCESS;
}