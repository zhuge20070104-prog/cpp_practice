#include <iostream>


int main(int argc, char* argv[]) {

    Number n1 {2};
    Number n2 {8};

    std::cout << std::boolalpha;

    std::cout << "n1 < n2: " << (n1 < n2) << std::endl;
    std::cout << "3 < n2: " << (3 < n2) << std::endl;
    std::cout << "n1 < 3: " << (n1 < 3) << std::endl;

    std::cout << "n1 > n2: " << (n1 > n2) << std::endl;
    std::cout << "3 > n2: " << (3 > n2) << std::endl;
    std::cout << "n1 > 3: " << (n1 > 3) << std::endl;

    std::cout << "n1 == n2: " << (n1 == n2) << std::endl;
    std::cout << "3 == n2: " << (3 == n2) << std::endl;
    std::cout << "n1 == 3: " << (n1 == 3) << std::endl;

    std::cout << "n1 != n2: " << (n1 != n2) << std::endl;
    std::cout << "3 != n2: " << (3 != n2) << std::endl;
    std::cout << "n1 != 3: " << (n1 != 3) << std::endl;

    std::cout << "n1 <= n2: " << (n1 <= n2) << std::endl;
    std::cout << "3 <= n2: " << (3 <= n2) << std::endl;
    std::cout << "n1 <= 3: " << (n1 <= 3) << std::endl;
    std::cout << "n1 >= n2: " << (n1 >= n2) << std::endl;
    std::cout << "3 >= n2: " << (3 >= n2) << std::endl;
    std::cout << "n1 >= 3: " << (n1 >= 3) << std::endl;
    return EXIT_SUCCESS;
}