#include <iostream>
#include <algorithm>
#include <ranges>


int main(int argc, char* argv[]) {
    auto infinite {std::views::iota(1)};

    for(auto i: std::views::iota(1, 11)) {
        std::cout << "Upper bound: " << i << std::endl;
    }

    for(auto i: std::views::iota(1) | std::views::take(30)) {
        std::cout << "Take: " << i << std::endl;
    }

    for(auto i: std::views::take(std::views::iota(1), 5)) {
        std::cout << "Raw composition: " << i << std::endl;
    }
    
    return EXIT_SUCCESS;
}