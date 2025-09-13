#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <future>
#include "asyc_out.hpp"

std::string the_func() {    
    std::string str("Hello from future!");
    std::cout << "string data address the func: " << (void*)str.data() << "\n"; 
    return str;
}


int main(int argc, char* argv[]) {  
    std::future<std::string> ftr = std::async(&the_func);
    std::cout << "Hello from main!\n";

    std::string str = ftr.get();
    std::cout << "string data address from main: " << (void*)str.data() << "\n";
    std::cout << str << std::endl;

    return EXIT_SUCCESS;
}