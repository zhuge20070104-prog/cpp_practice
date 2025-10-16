#include <iostream>


double add(double a, double b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    int x {2};
    int y {3};
    
    auto&& z {x + y};
    std::cout << "z: " << z << std::endl;

    auto&& add_func {add(2.2, 2.2)};
    std::cout << "add_func: " << add_func << std::endl;

    auto&& test = int{198};
    std::cout << "test: " << test << std::endl;
    std::cout << "&test: " << &test << std::endl;
    return EXIT_SUCCESS;
}
