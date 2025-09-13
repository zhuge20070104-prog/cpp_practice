#include <iostream>


int main(int argc, char* argv[]) {
    bool go {true};
    if(int speed {10}; go) {
        std::cout << "speed: " << speed << std::endl;
        if(speed > 5) {
            std::cout << "slow down" << std::endl;
        } else {
            std::cout << "all good" << std::endl;
        }
    } else {
        std::cout << "speed: " << speed << std::endl;
        std::cout << "stop" << std::endl;
    }
    return EXIT_SUCCESS;
}