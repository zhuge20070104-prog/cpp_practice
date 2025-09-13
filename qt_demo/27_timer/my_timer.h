#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_
#include "Poco/Timer.h"
#include "Poco/Stopwatch.h"
#include <iostream>


class MyTimer {
public:
    MyTimer() {
        sw.start();
    }

    void onTimer(Poco::Timer& timer) {
        std::cout << "Callback called after " << sw.elapsed()/ 1000<< " milliseconds." << std::endl;
    }

private:
    Poco::Stopwatch sw;
};

#endif