#include <exception>
#include <iostream>
#include <string>
#include <string_view>


int main(int argc, char* argv[]) {
    int a {98};
    int b {191};

    auto lambda1 {[&]() {
        std::cout << "++a: " << ++a << '\n';
        std::cout << "b: " << b << '\n';
    }};

    lambda1();
    return EXIT_SUCCESS;
}
