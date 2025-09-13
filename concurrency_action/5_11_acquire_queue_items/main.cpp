#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>
#include <string>
#include <vector>

// release-> acquire对也可以用于queue的 分批作业
std::vector<int> queue_data;
std::atomic<int> count;

void wait_for_more_items() {}

void process(int data) {
    std::cout << "thread ID: " << std::this_thread::get_id()
         << " process: " << data << std::endl;
}

void populate_queue() {
    unsigned const number_of_items = 20;
    queue_data.clear();
    for(unsigned i = 0; i < number_of_items; ++i) {
        queue_data.push_back(i);
    }

    count.store(number_of_items, std::memory_order_release);
}

void consume_queue_items() {
    while(true) {
        int item_index;
        // fetch_sub是一个读改写操作，返回修改之前的值，例如20个元素的时候，返回20
        // 需要减1，才能得到索引
        // 详情参考:  https://en.cppreference.com/w/cpp/atomic/atomic/fetch_sub
        if((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0) {
            wait_for_more_items();
            continue;
        }
        process(queue_data[item_index - 1]);
    }
}


int main(int argc, char* argv[]) {
    std::thread a(populate_queue);
    std::thread b(consume_queue_items);
    std::thread c(consume_queue_items);
    a.join();
    b.join();
    c.join();
    return EXIT_SUCCESS;
}