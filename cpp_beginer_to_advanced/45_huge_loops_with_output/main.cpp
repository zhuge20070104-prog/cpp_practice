#include <iostream>


int main(int argc, char* argv[]) {
    auto huge_for_loop = []() {
        for(std::size_t i = 0; i<100'000; ++i) {
            std::cout << "i: " << i << std::endl;
        }
        std::cout << "Done" << std::endl;
    };

    auto huge_while_loop = []() {
        std::size_t i = 0;
        while(i < 100'000) {
            std::cout << "i: " << i << std::endl;
            ++i;
        }
        std::cout << "Done" << std::endl;
    };

    huge_for_loop();
    huge_while_loop();
    
    return EXIT_SUCCESS;
}