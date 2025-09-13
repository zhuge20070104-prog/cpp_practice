#ifndef STOPWATCH11_H
#define STOPWATCH11_H

#include <chrono>

using namespace std::chrono;

class TimerBaseChrono {
public:
    using tick_t = unsigned long;
    // 构造函数，clears the timer
    TimerBaseChrono(): m_start(system_clock::time_point::min()) {}

    // clears the timer
    void Clear() {
        m_start = system_clock::time_point::min();
    }

    bool IsStarted() const {
        return m_start != system_clock::time_point::min();
    }

    // starts the timer
    void Start() {
        m_start = system_clock::now();
    }

    unsigned long GetMs() {
        if(IsStarted()) {
            system_clock::duration diff;
            diff = system_clock::now() - m_start;
            return (unsigned)(duration_cast<milliseconds>(diff).count());
        }
        return 0;
    }
private:
    system_clock::time_point m_start;
};

#include "stopwatch.h"
using StopWatch = basic_stopwatch<TimerBaseChrono>;
// 声明 stopwatch的测试方法，在外面调用
int test_stopwatch11(int test_no, unsigned long);
# endif