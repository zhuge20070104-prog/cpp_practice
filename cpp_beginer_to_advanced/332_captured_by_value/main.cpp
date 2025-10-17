#include <exception>
#include <iostream>
#include <string>
#include <string_view>


int main(int argc, char* argv[]) {
    
    int a {2};
    int b {10};

    // capturing by value
    auto lambda1 {[a, b](int c, int d) mutable {

        // works now, the operator() generated is non const because of mutable keyword
        ++a;
        std::cout << "a: " << a << '\n';
        std::cout << "b: " << b << '\n';
        std::cout << "c: " << c << '\n';
        std::cout << "d: " << d << '\n';
    }};

    lambda1(1, 9);
    return EXIT_SUCCESS;
}
