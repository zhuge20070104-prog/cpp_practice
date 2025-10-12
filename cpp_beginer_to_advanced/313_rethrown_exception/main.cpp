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
            try {
                do_something(i);
            }catch(SomethingWrong& ex_inner) {
                if(typeid(ex_inner) == typeid(Warning)) {
                    std::cout << "Inner block caught a Warning: " << ex_inner.what() << '\n';
                } else {
                    throw;
                }
            }
        } catch(SomethingWrong& ex_outer) {
            std::cout << "Outer block caught an exception: " << ex_outer.what() << '\n';
        }
    }
    return EXIT_SUCCESS;
}
