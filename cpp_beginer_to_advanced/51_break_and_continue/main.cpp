#include <iostream>


int main(int argc, char* argv[]) {
    
    std::size_t const COUNT = 20;
    auto for_continue_and_break = [&COUNT]() {
        for(std::size_t i = 0; i < COUNT; ++i) {
            if(i == 5) {
                continue;
            }

            if(i == 11) {
                break;
            }

            std::cout << "i: " << i << std::endl;
        }

        std::cout << "Loop done!" << std::endl;
    };

    auto while_continue_and_break = [&COUNT] () {
        std::size_t i = 0;
        while(i < COUNT) {
            if(i == 5) {
                ++i;
                continue;
            }

            if(i==11) {
                break;
            }

            std::cout << "i: " << i << std::endl;
            ++i;
        }

        std::cout << "Loop done!" << std::endl;
    };

    auto do_while_continue_and_break = [&COUNT] () {
        std::size_t i = 0;

        do {
            if(i == 5) {
                ++i;
                continue;
            }

            if(i == 11) {
                break;
            }

            std::cout << "i: " << i << std::endl;
            ++i;
        } while(i<COUNT);
        std::cout << "Loop done!" << std::endl;
    };

    for_continue_and_break();
    while_continue_and_break();
    do_while_continue_and_break();
    
    return EXIT_SUCCESS;
}