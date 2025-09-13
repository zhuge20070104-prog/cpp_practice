#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <boost/foreach.hpp>
#include <vector>
#include <cassert>
#include <future>
#include <chrono>
#include "asyc_out.hpp"


// 没有在主线程里面运行的任务，都是新线程
int main(int argc, char* argv[]) {
    aout << "Main thread id: " << std::this_thread::get_id() << "\n";
    std::vector<std::future<void>> futures;

    using namespace std::chrono_literals;
    for(int i=0; i<10; ++i) {
        auto fut = std::async([] {
            std::this_thread::sleep_for(2s);
            aout << std::this_thread::get_id() << " ";
        });

        futures.push_back(std::move(fut));
    }

    BOOST_FOREACH(std::future<void>& fut, futures) {
        fut.wait();
    };

    aout << std::endl;
    std::this_thread::sleep_for(10s);
    return EXIT_SUCCESS;
}