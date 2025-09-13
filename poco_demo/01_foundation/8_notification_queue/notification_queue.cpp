#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Random.h"
#include "Poco/AutoPtr.h"
#include <iostream>
#include <thread>
#include <string>

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Thread;
using Poco::Runnable;
using Poco::FastMutex;
using Poco::AutoPtr;


class WorkNotification: public Notification {
public:
    using Ptr = AutoPtr<WorkNotification>;

    WorkNotification(int data): _data(data) {}

    int data() const {
        return _data;
    }

private:
    int _data;
};


class Worker: public Runnable {
public:
    Worker(std::string const& name, NotificationQueue& queue): _name(name), _queue(queue) {}

    void run() {
        Poco::Random rnd;
        for(;;) {
            Notification::Ptr pNf(_queue.waitDequeueNotification());
            if(pNf) {
                WorkNotification::Ptr pWorkNf = pNf.cast<WorkNotification>();
                if(pWorkNf) {
                    {
                        FastMutex::ScopedLock lock(_mutex);
                        std::cout << _name << " got work notification " << pWorkNf->data() << std::endl;
                        std::cout << "Current thread ID: " << std::this_thread::get_id() << std::endl; 
                    }
                    Thread::sleep(rnd.next(200));
                }
            }else {
                break;
            }
        }
    }

private:
    std::string _name;
    NotificationQueue& _queue;
    static FastMutex _mutex;
};

FastMutex Worker::_mutex;

int main(int argc, char* argv[]) {
    NotificationQueue queue;
    Worker worker1 ("Worker 1", queue);
    Worker worker2 ("Worker 2", queue);
    Worker worker3 ("Worker 3", queue);

    // Start work threads
    ThreadPool::defaultPool().start(worker1);
    ThreadPool::defaultPool().start(worker2);
    ThreadPool::defaultPool().start(worker3);

    // Distribute some work
    for(int i=0; i<50; ++i) {
        queue.enqueueNotification(new WorkNotification(i));
    }

    while(!queue.empty())  {
        Thread::sleep(200);
    }

    Thread::sleep(500);

    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

    queue.wakeUpAll();
    ThreadPool::defaultPool().joinAll();

    return EXIT_SUCCESS;
}