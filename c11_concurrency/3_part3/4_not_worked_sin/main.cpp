#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include <chrono>
#include "asyc_out.hpp"


void to_sin(std::list<double>& list) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::for_each(list.begin(), list.end(), [](double& x) {
        x = sin(x);
    });
}

int main(int argc, char* argv[]) {  
    std::list<double> list_;
    // Access list from main thread
    double const pi = 3.141592;
    double const epsilon = 0.0000001;
    for(double x=0.0; x<2*pi +epsilon; x+=pi/16) {
        list_.push_back(x);
    }

    // 两个线程同时访问list, data race，翻车了
    // Start thread
    std::thread th(&to_sin, std::ref(list_));
    
    std::for_each(list_.begin(), list_.end(), [](double& x) {
        int count = static_cast<int>(10*x + 10.5);
        for(int i=0; i<count; ++i) {
            std::cout.put('*');
        }
        std::cout << "\n";
    });

    th.join();

    return EXIT_SUCCESS;
}