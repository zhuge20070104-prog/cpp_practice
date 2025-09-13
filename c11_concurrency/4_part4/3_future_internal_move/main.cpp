#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <future>
#include "asyc_out.hpp"

void the_func(std::promise<std::string>& prms) {
    std::string str("Hello from future!");
    std::cout << "string data address in the_func: " << (void*) str.data() << "\n";
    prms.set_value(str);
}

// future internal 不是移动，可能产生拷贝
int main(int argc, char* argv[]) {  
    std::promise<std::string> prms;

    std::thread th(&the_func, std::ref(prms));
    std::cout << "Hello from main!\n";

    std::future<std::string> ftr = prms.get_future();
    std::string str = ftr.get();
    std::cout << "string data address in main: " << (void*)str.data() << "\n";
    std::cout << str << std::endl;
    th.join();
    return EXIT_SUCCESS;
}