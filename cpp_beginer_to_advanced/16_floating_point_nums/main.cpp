#include <iostream>
// std::setprecision 需要include iomanip
#include <iomanip>


int main(int argc, char* argv[]) {
    float number1 {1.12345678901234567890f};
    double number2 {1.12345678901234567890};
    long double number3 {1.12345678901234567890L};

    std::cout << "size of(float): " << sizeof(float) << std::endl;
    std::cout << "size of(double): " << sizeof(double) << std::endl;
    std::cout << "size of(long double): " << sizeof(long double) << std::endl;

    std::cout << std::setprecision(20);
    std::cout << "number1 is: " << number1 << std::endl;
    std::cout << "number2 is: " << number2 << std::endl;
    std::cout << "number3 is: " << number3 << std::endl;


    // 浮点数精度问题
    // 浮点数处理不了这么高的精度，会报错
    // error: narrowing conversion of ‘192400023’ from ‘int’ to ‘float’ inside { } [-Wnarrowing]
    // float number4 {192400023};

    // 各种数据类型的精度
    // float 4字节，精度7位 [包含整数部分]
    // double 8字节，精度15位 [包含整数部分]
    // long double 12字节，精度> double [包含整数部分]

    // 精度问题
    // 浮点数精度问题
    // 浮点数处理不了这么高的精度，会报错
    // error: narrowing conversion of ‘192400023’ from ‘int’ to ‘float’ inside { } [-Wnarrowing]
    // float number4 {192400023};


    // 科学计数法
    double number5 {192400023};
    double number6 {1.92400023e8};
    double number7 {1.924e8};
    double number8 {0.00000000003498};
    double number9 {3.498e-11};

    std::cout << "number5 is: " << number5 << std::endl;
    std::cout << "number6 is: " << number6 << std::endl;
    std::cout << "number7 is: " << number7 << std::endl;
    std::cout << "number8 is: " << number8 << std::endl;
    std::cout << "number9 is: " << number9 << std::endl;

    // 除以0的问题
    double number10 {5.6};
    // 默认初始化列表初始化到0
    double number11 {};
    double number12 {};

    // 除以0 产生 inf 或者 -inf值
    double result {number10/ number11};
    std::cout << number10 << "/" << number11 << " yields "<< result << std::endl;


    return EXIT_SUCCESS;
}