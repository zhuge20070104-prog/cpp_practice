#include <iostream>
#include "scores.h"

int main(int argc, char* argv[]) {
   
    Scores s {"Science"};

    s.print_info();

    s[10] = 2;
    s.print_info();

    for(std::size_t i{0}; i<20; ++i) {
        s[i] = i + 23.2;
    }

    for(std::size_t i{0}; i<20; ++i) {
        std::cout << s[i] << " ";
    }

    std::cout << std::endl;

    const Scores s2 {"Mathematics"};
    s2.print_info();

    for(std::size_t i{0}; i<20; ++i) {
        std::cout << s2[i] << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}