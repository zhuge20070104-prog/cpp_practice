#include <iostream>

int main(int argc, char* argv[]) {
    int var1 {123};
    std::cout << "var1: " << var1 << std::endl;

    var1 = 55; // Assign
    std::cout << "var1: " << var1 << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;

    double var2 {44.55};
    std::cout << "var2: " << var2 << std::endl;
    var2 = 99.99; // Assign
    std::cout << "var2: " << var2 << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;

    bool state {false};
    std::cout << std::boolalpha;
    std::cout << "state: " << state << std::endl;
    state = true; // Assign
    std::cout << "state: " << state << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;


    auto var3 {333u}; // unsigned int, 注意auto变量
    var3 = -22; // 可以赋值，但是会有问题，危险
    std::cout << "var3: " << var3 << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;

    return EXIT_SUCCESS;
}