#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "size of boolean: " << sizeof(bool) << std::endl;
    std::cout << "size of char: " << sizeof(char) << std::endl;
    std::cout << "size of int: " << sizeof(int) << std::endl;
    std::cout << "size of float: " << sizeof(float) << std::endl;
    std::cout << "size of long: " << sizeof(long) << std::endl;
    std::cout << "size of double: " << sizeof(double) << std::endl;

    bool* p_bool;
    char* p_char;
    int* p_int;

    // 指针里面存储的就是一个16进制的地址，占8字节[64位机器]
    std::cout << "size of p_bool: " << sizeof(p_bool) << std::endl;
    std::cout << "size of p_char: " << sizeof(p_char) << std::endl;
    std::cout << "size of p_int: " << sizeof(p_int) << std::endl;

    return EXIT_SUCCESS;
}