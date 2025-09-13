#include <iostream>

void increment(int& value);
void print(int const& value);

int main(int argc, char* argv[]) {
    int int_var{3};
    increment(int_var);
    print(int_var);

    double double_var{3.6};
    int data = double_var;
    increment(data);
    print(double_var);
    return EXIT_SUCCESS;
}

void increment(int& value) {
    ++value;
    std::cout << "value incremented to: " << value << std::endl;
}

void print(int const& value) {
    std::cout << "value: " << value << std::endl;
}