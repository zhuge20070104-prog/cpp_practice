#include <iostream>


int main(int argc, char* argv[]) {
    
    // 无限循环
    auto for_loop_infinite = []() {
        for(std::size_t i = 0; true; ++i) {
            std::cout << i << ": I love C++" << std::endl;
        }
    };

    auto while_loop_infinite = []() {
        std::size_t i = 0;
        while(true) {
            std::cout << i << ": I love C++" << std::endl;
            ++i;
        }
    };

    auto do_while_loop_infinite = []() {
        std::size_t i = 0;  
        do {
            std::cout << i << ": I love C++" << std::endl;
            ++i;
        } while(true);
    };

    for_loop_infinite();
    while_loop_infinite();
    do_while_loop_infinite();

    return EXIT_SUCCESS;
}