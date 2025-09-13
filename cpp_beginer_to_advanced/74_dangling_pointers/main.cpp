#include <iostream>

enum danger_pt_t {
    UNINIT_POINTER,
    DELETED_POINTER,
    MULTI_POINTERS_POINTED_TO_SAME_ADDR,
    SOLUTION_1,
    SOLUTION_2,
    SOLUTION_3
};

struct danger_pointer_demo_t {

    void uninit_pointer() {
        int* p_number;
        std::cout << std::endl;
        std::cout << "Case 1: Uninitialized pointer: " << std::endl;
        std::cout << "p_number: " << p_number << std::endl;

        // Program received signal SIGSEGV, Segmentation fault
        // std::cout << "*p_number: " << *p_number << std::endl;
    }

    void deleted_pointer() {
        std::cout << std::endl;
        std::cout <<"Case 2: Deleted pointer: " << std::endl;
        int* p_number1 {new int(67)};
        std::cout << "*p_number1 (before delete): " << *p_number1 << std::endl;
        delete p_number1;
        // Delete 之后的值最好不要再用了，可能有坑
        // std::cout << "*p_number1 (after delete): " << *p_number1 << std::endl;
    }

    void multi_pointers_pointed_to_same_addr() {
        std::cout << std::endl;
        std::cout << "Case 3: Multiple pointers pointing to same address: " << std::endl;
        int* p_number3 {new int(83)};
        int* p_number4 {p_number3};
        std::cout << "p_number3: " << p_number3 << "-" << *p_number3 << std::endl;
        std::cout << "p_number4: " << p_number4 << "-" << *p_number4 << std::endl;

        delete p_number3;
        
        //p_number4 points to deleted memory. Dereferncing it will lead to
	    //undefined behaviour : Crash/ garbage or whatever
        // std::cout << "p_number4(after deleting p_number3): " << p_number4 << "-" << *p_number4 << std::endl; 
    }

    void solution1() {
        std::cout << std::endl;
        std::cout << "Solution1: " << std::endl;
        int* p_number5{nullptr};
        int* p_number6{new int(87)};

        // Check for nullptr before use
        if(p_number6 != nullptr) {
            std::cout << "*p_number6: " << *p_number6 << std::endl;
        } else {
            std::cout << "Invalid address" << std::endl;
        } 
    }

    void solution2() {
        std::cout << std::endl;
        std::cout << "Solution2: " << std::endl;
        int* p_number7 {new int{82}};
        std::cout << "p_number7 - " << p_number7 << "-" << *p_number7 << std::endl;

        delete p_number7;
        p_number7 = nullptr;
        if(p_number7) {
            std::cout << "*p_number7: " << *p_number7 << std::endl;
        } else {
            std::cout << "Invalid memory address!" << std::endl;
        }
    }

    void solution3() {
        std::cout << std::endl;
        std::cout << "Solution 3: " << std::endl;
        int* p_number8{new int{382}};
        int* p_number9{p_number8};

        std::cout << "p_number8 - " << p_number8 << "-" << *p_number8 << std::endl;
        if(p_number8) {
            std::cout << "p_number9 - " << p_number9 << "-" << *p_number9 << std::endl;
        }

        delete p_number8;
        p_number8 = nullptr;

        if(p_number8) {
            std::cout << "p_number9 - " << p_number9 << "-" << *p_number9 << std::endl;
        } else {
            std::cerr << "WARNING: Trying to use an invalid pointer" << std::endl;
        }
    }

    void operator()(danger_pt_t pt_type) {
        switch (pt_type) {
        case UNINIT_POINTER:
            uninit_pointer();
            break;
        case DELETED_POINTER:
            deleted_pointer();
            break;
        case MULTI_POINTERS_POINTED_TO_SAME_ADDR:
            multi_pointers_pointed_to_same_addr();
            break;
        case SOLUTION_1:
            solution1();
            break;
        case SOLUTION_2:
            solution2();
            break;
        case SOLUTION_3:
            solution3();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    danger_pointer_demo_t d_p_demo;
    d_p_demo(danger_pt_t::UNINIT_POINTER);
    d_p_demo(danger_pt_t::DELETED_POINTER);
    d_p_demo(danger_pt_t::MULTI_POINTERS_POINTED_TO_SAME_ADDR);
    d_p_demo(danger_pt_t::SOLUTION_1);
    d_p_demo(danger_pt_t::SOLUTION_2);
    d_p_demo(danger_pt_t::SOLUTION_3);
    std::cout << "Program is ending well" << std::endl;
    return EXIT_SUCCESS;
}