#include <iostream>


int main(int argc, char* argv[]) {
    // signed, unsigned, short, long 等等，都可以用来修饰整型
    int value1 {10};
    int value2 {-300};

    signed int value3 {20};
    signed int value4 {-400};

    std::cout << "value1: " << value1 << std::endl;
    std::cout << "value2: " << value2 << std::endl;
    std::cout << "value3: " << value3 << std::endl;
    std::cout << "value4: " << value4 << std::endl;
    
    return EXIT_SUCCESS;
}