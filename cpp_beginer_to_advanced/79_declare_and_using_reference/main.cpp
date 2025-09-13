#include <iostream>

int main(int argc, char* argv[]) {
    int int_data {33};
    double double_data {55};

    int& ref_int_data {int_data};
    double& ref_double_data {double_data};

    std::cout << "int_data: " << int_data << std::endl;
    std::cout << "&int_data: " << &int_data << std::endl;
    std::cout << "double_data: " << double_data << std::endl;
    std::cout << "&double_data: " << &double_data << std::endl;

    std::cout << "======================" << std::endl;
    std::cout << "ref_int_data: " << ref_int_data << std::endl;
    std::cout << "&ref_int_data: " << &ref_int_data << std::endl;
    std::cout << "ref_double_data: " << ref_double_data << std::endl;
    std::cout << "&ref_double_data: " << &ref_double_data << std::endl;
    
    int_data = 111;
    double_data = 67.2;
    
    std::cout << "int_data: " << int_data << std::endl;
    std::cout << "&int_data: " << &int_data << std::endl;
    std::cout << "double_data: " << double_data << std::endl;
    std::cout << "&double_data: " << &double_data << std::endl;

    std::cout << "======================" << std::endl;
    std::cout << "ref_int_data: " << ref_int_data << std::endl;
    std::cout << "&ref_int_data: " << &ref_int_data << std::endl;
    std::cout << "ref_double_data: " << ref_double_data << std::endl;
    std::cout << "&ref_double_data: " << &ref_double_data << std::endl;

    ref_int_data = 1012;
    ref_double_data = 1000.45;

    std::cout << "int_data: " << int_data << std::endl;
    std::cout << "&int_data: " << &int_data << std::endl;
    std::cout << "double_data: " << double_data << std::endl;
    std::cout << "&double_data: " << &double_data << std::endl;

    std::cout << "======================" << std::endl;
    std::cout << "ref_int_data: " << ref_int_data << std::endl;
    std::cout << "&ref_int_data: " << &ref_int_data << std::endl;
    std::cout << "ref_double_data: " << ref_double_data << std::endl;
    std::cout << "&ref_double_data: " << &ref_double_data << std::endl;

    return EXIT_SUCCESS;
}