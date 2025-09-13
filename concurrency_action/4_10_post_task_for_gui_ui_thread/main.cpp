#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <string>
#include <utility>
#include <deque>
#include <vector>
#include <algorithm>
#include <functional>


std::mutex m;
std::deque<std::packaged_task<void()>>  tasks;

bool gui_shutdown_message_received() {
    static int shutdown_count_idx {0};
    ++ shutdown_count_idx;
    if(shutdown_count_idx < 100) {
        return false;
    }
    return true;
}

void get_and_process_gui_message() {
    std::cout << "Process a GUI message\n";
}

void gui_thread() {
    while(!gui_shutdown_message_received())  {
        get_and_process_gui_message();
        std::packaged_task<void()> task; 
        {
            std::lock_guard<std::mutex> lk(m);
            if(tasks.empty())
                continue;
            task = std::move(tasks.front());
            tasks.pop_front();
        }
        task();
    }
}

template <typename Func>
std::future<void> post_task_for_gui_thread(Func f) {
    std::packaged_task<void()> task(f);
    std::future<void> res = task.get_future();
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task));
    return res;
}

int main(int argc, char* argv[]) {  
    std::thread gui_bg_thread(gui_thread);
    std::vector<std::future<void>> futures;
    for(int i=0; i<20; ++i) {
        auto fut =post_task_for_gui_thread([i](){
            std::cout << "Posted task [" << i << "]\n";
        });
        futures.push_back(std::move(fut));
    }

    std::for_each(futures.begin(), futures.end(), std::mem_fn(&std::future<void>::wait));
    gui_bg_thread.join();
    return EXIT_SUCCESS;
}