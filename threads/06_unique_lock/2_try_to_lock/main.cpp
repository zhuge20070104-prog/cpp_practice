#include <iostream>
#include <thread>
#include <list>
#include <mutex>


class Worker {
public: 
    void in_msg_recv_queue() {
        for(std::size_t i=0; i<100000; ++i) {
            std::cout << "Insert one element: " << i << std::endl;
            std::unique_lock<std::mutex> guard(mutex_);
            msg_recv_queue.push_back(i);
        }
    }


    bool out_msg_proc() {

            std::unique_lock<std::mutex> guard(mutex_, std::try_to_lock);
            if(guard.owns_lock()) {
                std::cout << "Owns lock success.." << std::endl;
                
                if(!msg_recv_queue.empty()) {
                    std::cout << "Delete one element: " << msg_recv_queue.front() << std::endl;
                    msg_recv_queue.pop_front();
                    return true;
                } 
                return false;
        } 
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
    std::mutex mutex_;
};


int main(int argc, char* argv[]) {
    Worker worker;
    std::thread out_msg_t(&Worker::out_msg_recv_queue, &worker);
    std::thread in_msg_t(&Worker::in_msg_recv_queue, &worker);
    out_msg_t.join();
    in_msg_t.join();
    return EXIT_SUCCESS;
}