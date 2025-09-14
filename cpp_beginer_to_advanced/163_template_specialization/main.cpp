#include <iostream>
#include <cstring>

template <typename T>
T maximum(T a, T b) {
    std::cout << "\ndefault template called\n";
    return (a > b) ? a: b;
}

template <>
const char* maximum(const char* a, const char* b) {
    std::cout << "\nspecialization called\n";
    return (std::strcmp(a, b) > 0) ? a : b;
}


int main(int argc, char* argv[]) {

    double d1 {22.38};
    double d2 {98.27};

    std::cout << "maximum(d1, d2): " << maximum(d1, d2) << '\n';
    
    const char* h {"hello"};
    const char* w {"world"};

    // calls the specialization template
    std::cout << "maximum(h, w): " << maximum(h, w) << '\n';

    return EXIT_SUCCESS;
}