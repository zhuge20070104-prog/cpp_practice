#include <iostream>

enum memory_leak_type_t {
    LEAK_BY_STACK_VAR,
    LEAK_BY_DOUBLE_ALLOC,
    LEAK_BY_NESTED_SCOPE
};

struct memory_leak_demo_t {

    void leak_by_stack_var() {

        int* p_number{new int{67}};
        int number = 55;
        // Now p_number points to address2 , but address1 is still in use by 
        // our program. But our program has lost access to that memory location.
        //Memory has been leaked.
        p_number = &number;
    }
    
    void leak_by_double_alloc() {
        int* p_number1 = new int(55);
        // memory with int{55} leaked.
        p_number1 = new int(44);
        delete p_number1;
        p_number1 = nullptr;
    }

    void leak_by_nested_scope() {
        {
            int* p_number2{new int{57}};
        }
        //Memory with int{57} leaked.
    }

    void operator()(memory_leak_type_t leak_t) {
        switch(leak_t) {
        case LEAK_BY_STACK_VAR:
            leak_by_stack_var();
            break;

        case LEAK_BY_DOUBLE_ALLOC:
            leak_by_double_alloc();
            break;
        
        case LEAK_BY_NESTED_SCOPE:
            leak_by_nested_scope();
            break;
        
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    memory_leak_demo_t leak_demo;
    leak_demo(LEAK_BY_STACK_VAR);
    leak_demo(LEAK_BY_DOUBLE_ALLOC);
    leak_demo(LEAK_BY_NESTED_SCOPE);

    std::cout << "Program ending well" << std::endl;
    return EXIT_SUCCESS;
} 