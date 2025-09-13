#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include <future>
#include "asyc_out.hpp"

class the_func_exception: public std::exception {
public:
    const char* what() const  noexcept  override{
        return "The func exception occurred!";
    }
};


std::string the_func() {    
    std::string str("Hello from future!");
    throw the_func_exception(); 
    return str;
}


int main(int argc, char* argv[]) {  
    std::future<std::string> ftr = std::async(&the_func);
    std::cout << "Hello from main!\n";

    try {
        std::string str = ftr.get();
        std::cout << str << std::endl;
    } catch(std::exception const& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    return EXIT_SUCCESS;
}