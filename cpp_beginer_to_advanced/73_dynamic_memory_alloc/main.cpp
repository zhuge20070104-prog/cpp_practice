#include <iostream>

enum pointer_t {
    POINTER_TO_STACK_VAR,
    DYNAMIC_HEAP_VAR,
    MULTI_DYNAMIC_VAR
};

struct pointer_demo_t {
    pointer_demo_t() {}

    void pointer_to_stack_var() {
        int number = 22;
        int* p_number = &number;

        std::cout << std::endl;
        std::cout << "Declaring pointer and assigning address: " << std::endl;
        std::cout << "number: " << number << std::endl;
        std::cout << "p_number: " << p_number << std::endl;
        std::cout << "&number: " << &number << std::endl;
        std::cout << "*p_number: " << *p_number << std::endl;

    }

    void dynamic_heap_var() {
        int* p_number4 {nullptr};
        p_number4 = new int;
        *p_number4 = 77; // Writting into dynamic allocated memeory
        std::cout << std::endl;
        std::cout << "Dynamic allocating memory: " << std::endl;
        std::cout << "*p_number4: " << *p_number4 << std::endl;
        delete p_number4;
        p_number4 = nullptr;
    }

    void multi_dynamic_var() {
        int* p_number5{new int};
        int* p_number6{new int(22)};
        int* p_number7{new int(23)};

        std::cout << std::endl;
        std::cout << "Initialize with valid memory address at declaration: " << std::endl;
        std::cout << "p_number5: " << p_number5 << std::endl;
        std::cout << "*p_number5: " << *p_number5 << std::endl;

        std::cout << "p_number6: " << p_number6 << std::endl;
        std::cout << "*p_number6: " << *p_number6 << std::endl;

        std::cout << "p_number7: " << p_number7 << std::endl;
        std::cout << "*p_number7: " << *p_number7 << std::endl;

        // Rember to release the memory
        delete p_number5;
        p_number5 = nullptr;

        delete p_number6;
        p_number6 = nullptr;

        delete p_number7;
        p_number7 = nullptr;

        p_number5 = new int(81);
        std::cout << "*p_number5: " << *p_number5 << std::endl;

        delete p_number5;
        p_number5 = nullptr;

        p_number5 = new int(99);
        std::cout << "*p_number5: " << *p_number5 << std::endl;

        delete p_number5;
        p_number5 = nullptr;   
    }

    void operator()(pointer_t pt_type) {
        switch (pt_type) {
        case POINTER_TO_STACK_VAR:
            pointer_to_stack_var();
            break;
        case DYNAMIC_HEAP_VAR:
            dynamic_heap_var();
            break;
        case MULTI_DYNAMIC_VAR:
            multi_dynamic_var();
            break;     
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    pointer_demo_t p_demo;
    p_demo(pointer_t::POINTER_TO_STACK_VAR);
    p_demo(pointer_t::DYNAMIC_HEAP_VAR);
    p_demo(pointer_t::MULTI_DYNAMIC_VAR);
    
    return EXIT_SUCCESS;
}