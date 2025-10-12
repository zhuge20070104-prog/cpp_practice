#include <exception>
#include <iostream>
#include <string>

void f1();
void f2();
void f3();

void exception_thrower() {
    std::cout << "Exception thrower started\n";
    throw 0;
    std::cout << "Exception thrower ended\n";
}

int main(int argc, char* argv[]) {
    f1();
    return EXIT_SUCCESS;
}

void f1() {
    std::cout << "Starting f1\n";
    try {
        f2();
    }catch(int ex) {
        std::cout << "Exception handled in f1: " << ex << '\n';
    }
    std::cout << "Ending f1\n";
}

void f2() {
    std::cout << "Starting f2\n";
    f3();
    std::cout << "Ending f2\n";
}

void f3() {
    std::cout << "Starting f3\n";
    exception_thrower();
    std::cout << "Ending f3\n";
}