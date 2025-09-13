#include <iostream>

enum test_t {
    SIZE_OF,
    POINTER_USAGE,
    CROSS_ASSIGN,
    DEREFERENCE
};

struct pointer_demo {
    void size_of() {
        int* p_number{nullptr};
        double* p_fractional_number{nullptr};

        std::cout << "sizeof(int): " << sizeof(int) << std::endl;
        std::cout << "sizeof(double): " << sizeof(double) << std::endl;
        std::cout << "sizeof(int*): " << sizeof(int*) << std::endl;
        std::cout << "sizeof(double*): " << sizeof(double*) << std::endl;

        std::cout << "sizeof(p_number): " << sizeof(p_number) << std::endl;
        std::cout << "sizeof(p_fractional_number):" << sizeof(p_fractional_number) << std::endl;
    }

    void pointer_usage() {
        int int_var{43};
        int* p_int(&int_var);
        std::cout << "int_var: " << int_var << std::endl;
        std::cout << "p_int (Address in Memory): " << p_int << std::endl;

        int int_var1{65};
        //You can also change the address stored in a pointer any time
        p_int = &int_var1;
        std::cout << "p_int with different address: " << p_int << std::endl;
    }

    void cross_assign() {
        int* p_int1{nullptr};
        double double_var{33.0};
        // Not compile
        // Can't cross assign between pointers of different types
        // p_int1 = &double_var;
    }

    void dereference() {
        int* p_int2{nullptr};
        int int_data {56};
        p_int2 = &int_data;
        std::cout << "value: " << *p_int2 << std::endl;
    }

    void operator()(test_t type)  {
        switch (type) {
        case SIZE_OF:
            size_of();
            break;
        case POINTER_USAGE:
            pointer_usage();
            break;
        case CROSS_ASSIGN:
            cross_assign();
            break;
        case DEREFERENCE:
            dereference();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    
    pointer_demo p_demo;
    p_demo(SIZE_OF);
    p_demo(POINTER_USAGE);
    p_demo(CROSS_ASSIGN);
    p_demo(DEREFERENCE);

    return EXIT_SUCCESS;
}