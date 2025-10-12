#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "exceptions.h"

void do_something(std::size_t i) {
    if(i == 2) {
        throw CriticalError("i is 2");
    } 

    if(i == 3) {
        throw SmallError("i is 3");
    }

    if(i == 5) {
        throw Warning("i is 5");
    }

    if(i == 7) {
        throw SomethingWrong("i is 7");
    }
}


int main(int argc, char* argv[]) {
    for(std::size_t i{0}; i<10; ++i) {
        try {
            do_something(i);
        }catch(SomethingWrong& ex) {
            std::cout << "Exception type: " << typeid(ex).name() << '\n';
            std::cout << "Exception message: " << ex.what() << '\n';
        }
    }
    return EXIT_SUCCESS;
}
