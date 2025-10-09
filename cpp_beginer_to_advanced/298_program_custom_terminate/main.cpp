#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <exception>


int main(int argc, char* argv[]) {
    std::set_terminate([]() {
        std::cout << "Inside lambda\n";
        std::cout << "Unhandled exception found, terminate the program in 10s...\n";
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::abort();
    });

    // unhandled exception - calls terminate and abort
    throw 0;

    return EXIT_SUCCESS;
}