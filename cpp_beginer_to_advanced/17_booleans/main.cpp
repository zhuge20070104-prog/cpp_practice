#include <iostream>

int main(int argc, char* argv[]) {
    // bool 是一种只能表达两种状态的类型，true/false 
    // bool 需要一个字节的内存用来存储对象
    // 一个字节能用来存储 256个不同的值，
    // 仅仅用来存储两个状态太浪费了，
    // 后面我们将要讲述如何用一个字节来存储更多数据

    bool red_light {true};
    bool green_light {false};

    if(red_light == true) {
        std::cout << "Stop!" << std::endl;
    } else {
        std::cout << "Go through!" << std::endl;
    }

    if(green_light) {
        std::cout << "The light is green!" << std::endl;
    } else {
        std::cout << "The light is not green!" << std::endl;
    }

    // sizeof bool
    std::cout << "sizeof(bool): " << sizeof(bool) << std::endl;

    // 打印bool
    // 1 --> true   
    // 0 --> false
    std::cout << std::endl;
    std::cout << "red_light: " << red_light << std::endl;
    std::cout << "green_light: " << green_light << std::endl;

    std::cout << std::boolalpha;
    std::cout << "red_light: " << red_light << std::endl;
    std::cout << "green_light: " << green_light << std::endl;

    return EXIT_SUCCESS;
}