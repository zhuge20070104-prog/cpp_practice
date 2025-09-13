#include <iostream>


int main(int argc, char* argv[]) {
    for(double multiplier = 4; auto i: {1, 2, 3 ,4, 5, 6, 7, 8, 9, 10}) {
        std::cout << "result: " << (i * multiplier) << std::endl;
    }
    return EXIT_SUCCESS;
}