#include <iostream>


int main(int argc, char* argv[]) {
    
    std::size_t const COUNT = 5;

    auto increment_for_loop = [&COUNT]() {
        std::cout << "Incrementing for loop" << std::endl;
        for(std::size_t i = 0; i < COUNT; ++i) {
            std::cout << "i: " << i << std::endl;
        }

        std::cout << std::endl;
    };


    auto decrement_for_loop = [&COUNT]() {
        std::cout << "Decrementing for loop" << std::endl;
        for(std::size_t i = COUNT; i > 0; --i) {
            std::cout << "i: " << i << std::endl;
        }
        std::cout << std::endl;
    };


    auto increment_while_loop = [&COUNT]() {
        std::cout << "Incrementing while loop" << std::endl;
        std::size_t i = 0;
        while(i < COUNT) {
            std::cout << "i: " << i << std::endl;
            ++i;
        }
        std::cout << std::endl;
    };

    auto decrement_while_loop = [&COUNT]() {
        std::cout << "Decrementing while loop" << std::endl;
        std::size_t i = COUNT;
        while(i > 0) {
            std::cout << "i: " << i << std::endl;
            --i;
        }
        std::cout << std::endl;
    };

    auto increment_do_while_loop = [&COUNT]() {
        std::cout << "Incrementing do while loop" << std::endl;
        std::size_t i = 0;
        do {
            std::cout << "i: " << i << std::endl;
            ++i;
        } while(i < COUNT);
        std::cout << std::endl;
    };

    auto decrement_do_while_loop = [&COUNT]() {
        std::cout << "Decrementing do while loop" << std::endl;
        std::size_t i = COUNT;

        do {
            std::cout << "i: " << i << std::endl;
            --i;
        } while(i > 0);
        std::cout << std::endl;
    };

    increment_for_loop();
    decrement_for_loop();
    increment_while_loop();
    decrement_while_loop();
    increment_do_while_loop();
    decrement_do_while_loop();
    
    return EXIT_SUCCESS;
}