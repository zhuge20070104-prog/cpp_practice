#include <thread>
#include <iostream>

#include <list>
#include <mutex>
#include <condition_variable>



class Worker {
public:
    void in_msg_queue() {
        for(int i=0; i<100000; ++i) {
            std::cout << "in_msg_queue insert one element: " << i << std::endl;
            // locked here using std::unique_lock
            std::unique_lock<std::mutex> lock_(mutex_); 
            msg_queue.push_back(i);
            // try to notify the wait thread, only when the other thread is in the wait process it works,
            // orelse it dosen't work
            condition.notify_one();
        }
    }


    void out_msg_queue() {
        int command = 0;
        while(true) {
            std::unique_lock<std::mutex> lock(mutex_);
            condition.wait(lock, [this](){
                if(!msg_queue.empty()) {
                    return true;
                }
                return false;
            });

            command = msg_queue.front();
        
            msg_queue.pop_front();
            lock.unlock();

            std::cout << "out_msg_queue executed, get an element" << std::endl;

            if(command == 99999) {
                std::cout << "Reach the limitation, break" << std::endl;
                break;
            } 
        }
    }

private:
    std::list<int> msg_queue;
    std::mutex mutex_;
    std::condition_variable condition;
};

int main(int argc, char* argv[]) {
    Worker worker;
    std::thread out_th(&Worker::out_msg_queue, &worker);
    std::thread in_th(&Worker::in_msg_queue, &worker);
    in_th.join();
    out_th.join();

    return EXIT_SUCCESS;
} 