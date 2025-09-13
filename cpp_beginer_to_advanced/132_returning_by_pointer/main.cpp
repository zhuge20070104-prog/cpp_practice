#include <iostream>

int* max_return_pointer(int* a, int* b) {
    if(*a > *b) {
        return a;
    } else {
        return b;
    }
}

int* max_input_by_value(int a, int b) {
    // Pointer to local variable returned
    if(a > b) {
        return &a;
    } else {
        return &b;
    }
}

int* sum(int* a, int* b) {
    // Pointer to local variable returned
    int result = *a + *b;
    return &result;
}

int main(int argc, char* argv[]) {
    int x {56};
    int y {45};

    int* p_max = max_return_pointer(&x, &y);
    std::cout << "*p_max: " << *p_max << std::endl;

    // int* p_sum = sum(&x, &y);
    // std::cout << "*p_sum: " << *p_sum << std::endl;

    // int* p_max_val = max_input_by_value(x, y);
    // std::cout << "*p_max_val: " << *p_max_val << std::endl;

    std::cout << "Done!" << std::endl;

    return EXIT_SUCCESS;
}