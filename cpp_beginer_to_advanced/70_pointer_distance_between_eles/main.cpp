#include <iostream>

int main(int argc, char* argv[]) {
    int scores[10] {11,12,13,14,15,16,17,18,19,20};

    int* pointer1 {scores + 0};
    int* pointer2 {scores + 8};

    std::cout << "pointer2 - pointer1: " << pointer2 - pointer1 << std::endl;
    std::cout << "pointer1 - pointer2: " << pointer1 - pointer2 << std::endl;

    std::ptrdiff_t pos_diff = pointer2 - pointer1;
    std::ptrdiff_t neg_diff = pointer1 - pointer2;

    std::cout << "pointer2 - pointer1: " << pos_diff << std::endl;
    std::cout << "pointer1 - pointer2: " << neg_diff << std::endl;
    // 就是sizeof(long) = 8
    std::cout << "sizeof(std::ptrdiff_t): " << sizeof(std::ptrdiff_t) << std::endl;

    return EXIT_SUCCESS;
}