#include <iostream>
#include <thread>
#include <list>
#include <mutex>


class Worker {
public: 
    void in_msg_recv_queue() {
        for(std::size_t i=0; i<100000; ++i) {
            std::cout << "Insert one element: " << i << std::endl;
            mutex1.lock();
            mutex2.lock();
            msg_recv_queue.push_back(i);
            mutex2.unlock();
            mutex1.unlock();
        }
    }


    bool out_msg_proc() {
        mutex1.lock();
        mutex2.lock();

        if(!msg_recv_queue.empty()) {
            std::cout << "Delete one element: " << msg_recv_queue.front() << std::endl;
            msg_recv_queue.pop_front();
            mutex2.unlock();
            mutex1.unlock();
            return true;
        }

        mutex2.unlock();
        mutex1.unlock();
        return false;
    }


    void out_msg_recv_queue() {
        for(int i=0; i<100000; ++i) {
            if(out_msg_proc()) {

            } else {
                std::cout << "list is empty" << std::endl;
            }
        }
    }

private:    
    std::list<int> msg_recv_queue;
    std::mutex mutex1;
    std::mutex mutex2;
};


int main(int argc, char* argv[]) {
    Worker worker;
    std::thread out_msg_t(&Worker::out_msg_recv_queue, &worker);
    std::thread in_msg_t(&Worker::in_msg_recv_queue, &worker);
    out_msg_t.join();
    in_msg_t.join();
    return EXIT_SUCCESS;
}