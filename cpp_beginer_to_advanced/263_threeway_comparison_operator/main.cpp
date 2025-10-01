#include <iostream>
#include <string>
#include <limits>


int main(int argc, char* argv[]) {

    int x {2};
    int y {2};
    
    // <=> doesn't return an int
    auto result {x <=> y};

    std::cout << std::boolalpha;

    std::cout << "result > 0: " << (result > 0) << "\n";
    std::cout << "result < 0: " << (result < 0) << "\n";
    std::cout << "result == 0: " << (result == 0) << "\n";
    std::cout << "result >= 0: " << (result >= 0) << "\n";
    std::cout << "result <= 0: " << (result <= 0) << "\n";
    std::cout << "result != 0: " << (result != 0) << "\n";


    int a{3};
    int b{3};

    // defining feature of strong ordering
    std::cout << "a < b: " << (a < b) << "\n";
    std::cout << "a == b: " << (a == b) << "\n";
    std::cout << "a > b: " << (a > b) << "\n";

    std::string s1{"hello"};
    std::string s2{"HELLO"};

    std::cout << "s1 < s2: " << (s1 < s2) << "\n";
    std::cout << "s1 == s2: " << (s1 == s2) << "\n";
    std::cout << "s1 > s2: " << (s1 > s2) << "\n";

    double d1 {1.1};
    double d2 {std::numeric_limits<double>::quiet_NaN()};

    // defining feature of partial ordering
    // partial ordering - can't compare d1 to d2, d2 is not representable in memory

    std::cout << "d1 < d2: " << (d1 < d2) << "\n";
    std::cout << "d1 == d2: " << (d1 == d2) << "\n";
    std::cout << "d1 > d2: " << (d1 > d2) << "\n";

    return EXIT_SUCCESS;
}