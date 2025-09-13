#include <iostream>

void print_sum(int* param1, int* param2) {
    std::cout << "sum: " << (*param1 + *param2) << std::endl;
}

int main(int argc, char* argv[]) {
    double a {3.1};
    double b {12.2};
    int c = a;
    int d = b;
    print_sum(&c, &d);
    return EXIT_SUCCESS;
}