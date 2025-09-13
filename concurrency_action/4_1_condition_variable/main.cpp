#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

bool more_data_to_prepare() {
    static int more_data_idx {0};
    ++ more_data_idx;
    return more_data_idx <= 1001;
}

struct data_chunk {};

data_chunk prepare_data() {
    return data_chunk();
}

void process(data_chunk& data) {}

bool is_last_chunk(data_chunk& data) {
    static int data_chunk_idx{0};
    ++ data_chunk_idx;
    return data_chunk_idx > 1000;
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread() {
    while(more_data_to_prepare()) {
        data_chunk const data = prepare_data();
        // 写入时用lock_guard锁住，lock_guard不能半路解锁，不能手动unlock
        // 不能用于con::wait
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    } 
}

void data_processing_thread() {
    while(true) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [&](){return !data_queue.empty(); });
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        process(data);
        if(is_last_chunk(data)) {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}