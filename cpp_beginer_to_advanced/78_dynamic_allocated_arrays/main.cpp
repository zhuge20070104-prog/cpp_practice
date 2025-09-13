#include <iostream>
#include <algorithm>
#include <numeric>


enum dynamic_array_t {
    DYNAMIC_ARRAY,
    STATIC_VS_DYNAMIC_ARRAY
};

struct dynamic_array_demo_t {
    void dynamic_array() {
        std::size_t const size = 10;
        // p_salaries array will contains garbage values
        double* p_salaries {new double[size]};

        // 因为用了初始化列表，所有值被初始化成 0
        int* p_students {new (std::nothrow) int[size]{}};

        // Allocating memory space
        // for an array  of size double
        // vars. First 5 will be initialized
        //with 1,2,3,4,5, and the 
        //rest will be 0's.
        double* p_scores {new (std::nothrow) double[size]{1, 2, 3, 4, 5}};

        if(p_scores) {
            std::cout << "sizeof scores (it's a regular pointer): " << sizeof(p_scores) << std::endl;
            std::cout << "Successfully allocated memory for scores." << std::endl;
            // Print out elements. Can use regular array access notation, or pointer arithmetic
            for(std::size_t i{}; i<size; ++i) {
                std::cout << "value: " << p_scores[i] << " : " << *(p_scores+i) << std::endl;
            }
        }

        delete [] p_salaries;
        p_salaries = nullptr;
        delete [] p_students;
        p_students = nullptr;
        delete [] p_scores;
        p_scores = nullptr;
    }


    void static_vs_dynamic_array() {
        std::cout << "=========================================" << std::endl;
        int scores[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::cout << "scores size: " << std::size(scores) << std::endl;
        std::for_each(scores, scores + std::size(scores), [](int const& score){
            std::cout << "value: " << score << std::endl;
        });

        int* p_scores = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::for_each(p_scores, p_scores + 10, [](int const& score) {
            std::cout << "value: " << score << std::endl;
        });

        delete [] p_scores;
        p_scores = nullptr;
    }

    void operator()(dynamic_array_t array_t) {
        switch(array_t) {
        case DYNAMIC_ARRAY:
            dynamic_array();
            break;
        case STATIC_VS_DYNAMIC_ARRAY:
            static_vs_dynamic_array();
            break;
        default:
            break; 
        }
    }
};

int main(int argc, char* argv[]) {
    dynamic_array_demo_t d_arr_demo;
    d_arr_demo(dynamic_array_t::DYNAMIC_ARRAY);
    d_arr_demo(dynamic_array_t::STATIC_VS_DYNAMIC_ARRAY);
    
    return EXIT_SUCCESS;
}