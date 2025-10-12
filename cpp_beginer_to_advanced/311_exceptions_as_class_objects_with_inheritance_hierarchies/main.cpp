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
        }catch(CriticalError& ex) {
            std::cout << "CriticalError exception is handled: " << ex.what() << '\n';
        }catch(SmallError& ex) {
            std::cout << "SmallError exception is handled: " << ex.what() << '\n';
        }catch(Warning& ex) {
            std::cout << "Warning exception is handled: " << ex.what() << '\n';
        }catch(SomethingWrong& ex) {
            std::cout << "SomethingWrong exception is handled: " << ex.what() << '\n';
        }
    }
    return EXIT_SUCCESS;
}
