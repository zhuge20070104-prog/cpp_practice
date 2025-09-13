#include "Poco/Timer.h"
#include "Poco/Thread.h"
#include "Poco/Stopwatch.h"

#include <iostream>

using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;


class TimerExample {
public:
    TimerExample() {
        _sw.start();
    }

    void onTimer(Timer& timer) {
        std::cout << "Callback called after " << _sw.elapsed()/1000 << " miliiseconds." << std::endl;
    }

private:
    Stopwatch _sw;
};

int main(int argc, char* argv[]) {
    TimerExample example;
    // 250 start interval
    // 500 peridic interval
    // 250 750 1250 1750
    Timer timer(250, 500);

    timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));
    Thread::sleep(5000);
    timer.stop();

    return EXIT_SUCCESS;
}
