#include <iostream>


int main(int argc, char* argv[]) {
    auto pure_print = []() {
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;

        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
    };

    auto do_while_loop = []() {
        int const COUNT = 0;
        std::size_t i = 0;
        do {
            std::cout << i << ": I love C++" << std::endl;
            ++i;
        } while(i < COUNT);
        std::cout << "Loop done!" << std::endl;
    };

    pure_print();
    do_while_loop();
    
    return EXIT_SUCCESS;
}