#include <iostream>


int main(int argc, char* argv[]) {
    
    auto print_duplicate = []() {
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

    auto while_loop = []() {
        std::size_t COUNT = 100;
        std::size_t i = 0;

        while(i<COUNT) {
            std::cout << i << ": I love C++" << std::endl;
            ++i;
        }
    };

    print_duplicate();
    while_loop();

    std::cout << "Loop done!" << std::endl;
    return EXIT_SUCCESS;
}