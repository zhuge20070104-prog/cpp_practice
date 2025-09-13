#include "Poco/Activity.h"
#include "Poco/Thread.h"

#include <iostream>
#include <thread>

using Poco::Activity;
using Poco::Thread;

class ActivityExample {
public:
    ActivityExample(): _activity(this, &ActivityExample::runActivity) {

    }

    void start() {
        _activity.start();
    }

    void stop() {
        _activity.stop();
        _activity.wait();
    }

protected:
    void runActivity() {
        while (!_activity.isStopped()) {
            std::cout << "run Activity thread ID:" << std::this_thread::get_id() << std::endl;
            std::cout << "Activity running." << std::endl;
            Thread::sleep(250);
        }
        std::cout << "Activity stopped." << std::endl;
    }
private:
    Activity<ActivityExample> _activity;
};


int main(int argc, char* argv[]) {
    ActivityExample example;
    example.start();
    Thread::sleep(2000);
    example.stop();
    example.start();
    example.stop();
    std::cout << "Main Thread Id: " << std::this_thread::get_id() << std::endl;
    return EXIT_SUCCESS;
}