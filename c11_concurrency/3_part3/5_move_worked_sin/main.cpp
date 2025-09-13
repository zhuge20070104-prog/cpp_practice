#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
#include "asyc_out.hpp"


void to_sin(std::list<double>&& list) {
    std::for_each(list.begin(), list.end(), [](double& x) {
        x = sin(x);
    });

    std::for_each(list.begin(), list.end(), [](double& x) {
        int count = static_cast<int>(10*x + 10.5);
        for(int i=0; i<count; ++i) {
            std::cout.put('*');
        }
        std::cout << "\n";
    });
}

// 直接转移所有权到线程2，
// 线程1失去了list的所有权
// 我们还需要一个机制把list传回线程1
int main(int argc, char* argv[]) {  
    std::list<double> list_;
    // Access list from main thread
    double const pi = 3.141592;
    double const epsilon = 0.0000001;
    for(double x=0.0; x<2*pi +epsilon; x+=pi/16) {
        list_.push_back(x);
    }

    // Start thread
    std::thread th(&to_sin, std::move(list_));
    th.join();
    

    return EXIT_SUCCESS;
}