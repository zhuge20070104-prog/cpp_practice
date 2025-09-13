#include <iostream>


int main(int argc, char* argv[]) {
    
    // 逗号操作符合并
    // 把两个或 更多表达式合并成一个表达式
    // 逗号表达式的值是右操作符的值
    int increment = 5;
    int number1 = 10;
    int number2 = 20;
    int number3 = 25;

    int result = (number1 *= ++increment, number2 - (++increment), number3 += ++increment);
    std::cout << "number1: " << number1 << std::endl;
    std::cout << "number2: " << number2 << std::endl;
    std::cout << "number3: " << number3 << std::endl;
    std::cout << "result: " << result << std::endl;

    return EXIT_SUCCESS;
}