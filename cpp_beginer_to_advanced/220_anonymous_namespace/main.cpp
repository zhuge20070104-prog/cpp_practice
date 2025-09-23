#include <iostream>

namespace {
    double add(double a, double b);
}

namespace {
    double add(double a, double b) {
        return a + b;
    }
}

int main(int argc, char* argv[]) {
    // anonymous namespace names are accessible in the main.cpp only
    std::cout << add(2, 2) << '\n';
    
    return EXIT_SUCCESS;
}

