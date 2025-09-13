#include <iostream>

int main(int argc, char* argv[]) {
    int number = 240;
    int* num_ptr = &number;
    std::cout << "The address of number is: " << num_ptr << std::endl;

    // 指针不仅是一个地址，还指向内存中对应的一个对象，
    // 不能随便将不同类型的地址赋值给指针,例如double类型的地址不能赋值给int指针
    // double number_2 = 13.5;
    // num_ptr = &number_2;
    return EXIT_SUCCESS;
}