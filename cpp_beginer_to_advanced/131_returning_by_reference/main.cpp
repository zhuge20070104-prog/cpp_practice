#include <iostream>

int& max_return_reference(int& a, int& b) {
    if(a>b) {
        return a;
    } else {
        return b;
    }
}

int& sum(int& a, int& b) {
    int result = a + b;
    // Reference to local variable returned
    // 什么类型接都不行，出了函数，result就消失了，不能引用返回。
    return result;
}

int& max_input_by_value(int a, int b) {
    // Reference to local variable returned
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int main(int argc, char* argv[]) {
    int x {14};
    int y {9};
    // reference
    int& ref_max = max_return_reference(x, y);
    // copy
    int val = max_return_reference(x, y);
    std::cout << "ref_max: " << ref_max << std::endl;
    std::cout << "val: " << val << std::endl;

    // 这个打印会有问题，因为临时变量消失了，在函数结束时
    // int result = sum(x, y);
    // std::cout << "result: " << result << std::endl;

    // 这个打印会有问题，因为临时变量消失了，在函数结束时
    // int& max_val = max_input_by_value(x, y);
    // std::cout << "max_val: " << max_val;
    return EXIT_SUCCESS;
}