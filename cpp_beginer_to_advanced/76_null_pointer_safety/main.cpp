#include <iostream>

enum null_check_type_t {
    DIRECT_CHECK,
    CHECK,
    DELETE_NULL_PTR
};


struct null_pointer_demo_t {

    void direct_check() {
        std::cout << std::endl;
        std::cout << "Verbose nullptr check: " << std::endl;
        int* p_number{};
        p_number = new int(7);

        if(p_number != nullptr) {
            std::cout << "p_number points to a valid address: " << p_number << std::endl;
            std::cout << "*p_number: " << *p_number << std::endl;
        } else {
            std::cout << "p_number points to an invalid address." << std::endl;
        }
        delete p_number;
        p_number = nullptr;
    }

    void check() {
        std::cout << std::endl;
        std::cout << "nullptr check: " << std::endl;
        int* p_number{};
        p_number = new int(7);

        if(p_number) {
            std::cout << "p_number points to a valid address: " << p_number << std::endl;
            std::cout << "*p_number: " << *p_number << std::endl;
        } else {
            std::cout << "p_number points to an invalid address." << std::endl;
        }  

        delete p_number;
        p_number = nullptr;
    }

    void delete_null_ptr() {
        int* p_number1 {};
        //It is OK call delete on a nullptr
	    //Calling delete on a nullptr is OK
        delete p_number1;
        p_number1 = nullptr;
    } 
    
    void operator()(null_check_type_t null_type){
        switch(null_type) {
            case DIRECT_CHECK:
            direct_check();
            break;

            case CHECK:
            check();
            break;

            case DELETE_NULL_PTR:
            delete_null_ptr();
            break;

            default:
            break; 
        }
    }
};


int main(int argc, char* argv[]) {
    null_pointer_demo_t demo;
    demo(DIRECT_CHECK);
    demo(CHECK);
    demo(DELETE_NULL_PTR);

    return EXIT_SUCCESS;
}