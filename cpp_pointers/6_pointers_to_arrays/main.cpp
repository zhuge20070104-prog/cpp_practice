#include <iostream>

int main(int argc, char* argv[]) {
    // array的名字包含了他的首地址，不需要用取地址操作符
    double values[10];
    double* p_values = values;
    std::cout << "value array address: " << values << std::endl;
    std::cout << "p_values: " << p_values << std::endl;

    // 用指针变量来遍历整型数组的地址
    // 整型数组，每次地址 + 4
    int numbers[10];
    int* p_numbers = numbers;
    for(int i=0; i<10; ++i) {
        std::cout << "numbers address: " << i << " : " << (p_numbers + i) << std::endl;
    }
    return EXIT_SUCCESS;
}