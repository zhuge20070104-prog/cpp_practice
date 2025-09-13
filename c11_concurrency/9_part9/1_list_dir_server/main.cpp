#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <boost/foreach.hpp>
#include <vector>
#include <string>
#include <cassert>
#include <future>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <deque>
#include "asyc_out.hpp"
#include "clocker.hpp"

using path_type = boost::filesystem::path;
int const NUM_THREADS = 8;

template <typename T>
class MsgQueue {
    std::deque<T> queue_;
    std::condition_variable cond_;
    std::mutex mutex_;

public:
    void send(T&& msg) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push_front(std::move(msg));
        }
        cond_.notify_one();
    }

    T receive() {
        // 注意这里必须用std::unique_lock，因为cond_.wait的时候会调用lock和unlock接口
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this](){return !queue_.empty();});
        T msg = std::move(queue_.back());
        queue_.pop_back();
        return msg;
    }
};


void list_dir_server(MsgQueue<path_type>& dir_queue, MsgQueue<std::string>& file_queue) {
    for(;;) {
        path_type dir = dir_queue.receive();
        boost::filesystem::directory_iterator it(dir);
        for(auto& sub_path: it) {
            if(boost::filesystem::is_directory(sub_path)) {
                auto path_ = sub_path.path();
                dir_queue.send(std::move(path_));
            } else {
                auto path_leaf =  sub_path.path().filename().string();
                file_queue.send(std::move(path_leaf));
            }
        }
    }
}

void print_server(MsgQueue<std::string>& name_queue) {
    for(;;) {
        std::string name = name_queue.receive();
        aout << name << "\n";
    }
}

void list_tree(path_type&& root_dir) {
    MsgQueue<path_type> dir_queue;
    MsgQueue<std::string> file_queue;
    dir_queue.send(std::move(root_dir));

    std::vector<std::future<void>> futures;
    for(int i=0; i<NUM_THREADS; ++i) {
        futures.push_back(std::async(std::launch::async, &list_dir_server, 
            std::ref(dir_queue),
            std::ref(file_queue)));
    }

    futures.push_back(std::async(std::launch::async, &print_server, std::ref(file_queue)));

    try {
        while(!futures.empty()) {
            auto ftr = std::move(futures.back());
            futures.pop_back();
            ftr.get();
        }
    } catch(boost::filesystem::filesystem_error& err) {
        aout << "File system error: " << err.code().message() << "\n";
    } catch(std::exception& ex) {
        aout << "Exception: " << ex.what() << "\n";
    } catch(...) {
        aout << "Unknown exception\n";
    }
}

int main(int argc, char* argv[]) {
    path_type root_dir("/home/fredric/code");
    list_tree(std::move(root_dir));

    return EXIT_SUCCESS;
}