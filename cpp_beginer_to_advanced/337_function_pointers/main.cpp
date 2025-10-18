#include <exception>
#include <iostream>
#include <string>
#include <string_view>

double function(double a, double b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    // setting a function pointer to function()
    // auto or return type can be used
    // param names are optional
    // & is optional
    auto (*f_ptr)(double, double) {&function};
    std::cout << "f_ptr(2.8, 6.2): " << f_ptr(2.8, 6.2) << std::endl;
    
    // possible, but auto can't be used here
    int (*f_ptr2) () = nullptr;
    auto f_ptr3 {function};
    auto* f_ptr4 {function};

    return EXIT_SUCCESS;
}
