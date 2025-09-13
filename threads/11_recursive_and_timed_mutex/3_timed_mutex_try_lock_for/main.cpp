#include <thread>
#include <iostream>

#include <list>
#include <mutex>
#include <condition_variable>

// TODO: Use timed_mutex here

class Worker {
public:
    void in_msg_queue() {
        for(int i=0; i<100000; ++i) {
            
            // locked here using std::unique_lock
            if(mutex_.try_lock_for(std::chrono::milliseconds(0))){
                std::cout << "in_msg_queue insert one element: " << i << std::endl;
                msg_queue.push_back(i);
                mutex_.unlock();
            } else {
                // 没拿到锁就休息一下等待下次拿
                std::this_thread::sleep_for(std::chrono::milliseconds(0));
            }
            
        }
    }


    void out_msg_queue() {
        int command = 0;
        while(true) {
            
            if(mutex_.try_lock_for(std::chrono::milliseconds(0))){
                if(!msg_queue.empty()) {
                    command = msg_queue.front();
                    msg_queue.pop_front();
                    std::cout << "out_msg_queue executed, get an element" << std::endl;
                }
                mutex_.unlock();
            } else {
                // 这次没拿到，就等一会再拿锁
                std::this_thread::sleep_for(std::chrono::milliseconds(0)); 
            }

            if(command == 99999) {
                std::cout << "Reach the limitation, break" << std::endl;
                break;
            } 
        }
    }

private:
    std::list<int> msg_queue;
    std::timed_mutex mutex_;
};

int main(int argc, char* argv[]) {
    Worker worker;
    std::thread out_th(&Worker::out_msg_queue, &worker);
    std::thread in_th(&Worker::in_msg_queue, &worker);
    in_th.join();
    out_th.join();

    return EXIT_SUCCESS;
} 