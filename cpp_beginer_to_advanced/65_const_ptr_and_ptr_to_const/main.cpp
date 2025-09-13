#include <iostream>

enum func_t {
    RAW_VAR_CAN_BE_MODIFIED,
    GENERAL_POINTER,
    POINTER_TO_CONST_DATA,
    POINTER_AND_POINTED_TO_CONST,
    POINTER_CONST
};

struct const_demo_func_t {
    const_demo_func_t() {}

    void raw_var_can_be_modified() {
        std::cout << std::endl;
        std::cout << "Raw variable that can be modified" << std::endl;
        int number {5};
        std::cout << "number: " << number << std::endl;
        std::cout << "&number: " << &number << std::endl;

        // 修改
        number = 12;
        number += 7;
        std::cout << "number: " << number << std::endl;
        std::cout << "&number: " << &number << std::endl;
        std::cout << std::endl;
    }

    void general_pointer() {
        int* p_number1 {nullptr};
        int number1 {23};
        p_number1 = &number1;
        std::cout << "Pointer and value pointed to: Both modifiable: " << std::endl;

        std::cout << "p_number1: " << p_number1 << std::endl;
        std::cout << "*p_number1: " << *p_number1 << std::endl;
        std::cout << "number1: " << number1 << std::endl;

        // Change the pointed to value through pointer
        std::cout << std::endl;
        std::cout << "Modifying the value pointed to p_number1 through the pointer: " << std::endl;
        *p_number1 = 432;
        std::cout << "p_number1: " << p_number1 << std::endl;
        std::cout << "*p_number1: " << *p_number1 << std::endl;
        std::cout << "number1: " << number1 << std::endl;


        std::cout << std::endl;
        std::cout << "Changing the pointer itself to make it point somewhere else" << std::endl;
        int number2 {56};
        p_number1 = &number2;
        std::cout << "p_number1: " << p_number1 << std::endl;
        std::cout << "*p_number1: " << *p_number1 << std::endl;
        std::cout << "number1: " << number1 << std::endl;
        std::cout << "number2: " << number2 << std::endl;
        std::cout << std::endl;
    }

    void pointer_to_const_data() {
        std::cout << "Pointer is modifiable, pointed to value is constant: " << std::endl;
        int number3 = 632;
        int const* p_number3{&number3};

        std::cout << "p_number3: " << p_number3 << std::endl;
        std::cout << "*p_number3: " << *p_number3 << std::endl;
        std::cout << "Modified the value pointed to by p_number3 through the pointer (Compile Error): " << std::endl;
        // error: assignment of read-only location ‘* p_number3’
        // *p_number3 = 444;

        //Although we can't change what's pointed to by p_number3,
	    //we can still change where it's pointing
        std::cout << std::endl;
        std::cout << "Changing the address pointed to by p_number3: " << std::endl;
        int number4 = 872;
        p_number3 = &number4;
        std::cout << "p_number3: " << p_number3 << std::endl;
        std::cout << "*p_number3: " << *p_number3 << std::endl;
        std::cout << std::endl;
    }

    void pointer_and_pointed_to_const() {
        int const number5 {459};
        int const* const p_number5{&number5};

        std::cout << "Pointer is constant, value pointed to is constant: " << std::endl;
        std::cout <<"p_number5: " << p_number5 << std::endl;
        std::cout << "*p_number5: " << *p_number5 << std::endl;

        std::cout << "Changing value pointed to by p_number5 through the pointer (Compile Error)" << std::endl;
        // *p_number5 = 222;

        std::cout << "Changing the pointer p_number5 address itself (Compile error)" << std::endl;

        int number6 {333};
        // p_number5 = &number6;

        std::cout << std::endl;
    }

    void pointer_const() {
        std::cout << "Pointer is constant, pointed to value can change: " << std::endl;
        int number7 = 982;
        int* const p_number7 = &number7;
        std::cout << "p_number7: " << p_number7 << std::endl;
        std::cout << "*p_number7: " << *p_number7 << std::endl;
        
        std::cout << "Changing value pointed to through p_number7 pointer: " << std::endl;
        *p_number7 = 456;
        std::cout << "The value pointed to by p_number7 now is : " << *p_number7 << std::endl;

        int number8 {2928};
        std::cout << "Changing the address where p_number7 is pointing (Compile Error)." << std::endl;
        // p_number7 = &number8;
    }

    void operator()(func_t f) {
        switch (f) {
        case RAW_VAR_CAN_BE_MODIFIED:
            raw_var_can_be_modified();
            break;
        case GENERAL_POINTER:
            general_pointer();
            break;
        case POINTER_TO_CONST_DATA:
            pointer_to_const_data();
            break;
        case POINTER_AND_POINTED_TO_CONST:
            pointer_and_pointed_to_const();
            break;
        case POINTER_CONST:
            pointer_const();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    const_demo_func_t demo;
    demo(func_t::RAW_VAR_CAN_BE_MODIFIED);
    demo(func_t::GENERAL_POINTER);
    demo(func_t::POINTER_TO_CONST_DATA);
    demo(func_t::POINTER_AND_POINTED_TO_CONST);
    demo(func_t::POINTER_CONST);
    return EXIT_SUCCESS;
}