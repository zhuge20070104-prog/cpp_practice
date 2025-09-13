#include <iostream>

int main(int argc, char* argv[]) {
    char const* message {"Hello world!"};
    std::cout << "message: " << message << std::endl;
    // *message = "B" 编译错误， char const* 指针常量，不让改
    // 输出第一个字符 H
    std::cout << "*message: " << *message << std::endl;

    // Char数组可以改
    char message1[] {"Hello world!"};
    message1[0] = 'B';
    std::cout << "message1: " << message1 << std::endl;
    return EXIT_SUCCESS;
}