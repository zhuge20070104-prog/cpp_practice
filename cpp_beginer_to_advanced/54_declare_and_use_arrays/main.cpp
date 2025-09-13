#include <iostream>


int main(int argc, char* argv[]) {
    auto read_junk_data = []() {
        std::cout << "Read junk data" << std::endl;
        int scores[10];
        std::cout << " scores[0] : " << scores[0] << std::endl;
        std::cout << " scores[1] : " << scores[1] << std::endl;
        std::cout << std::endl;
    };

    auto read_junk_data_with_loop = []() {
        std::cout << "Read junk data with a loop" << std::endl;
        int scores[10];
        for(std::size_t i = 0; i < 10; ++i) {
            std::cout << "scores [" << i << "]: " << scores[i] << std::endl;
        }
        std::cout << std::endl;
    };

    auto array_assign = []() {
        std::cout << "Array assign" << std::endl;
        int scores[10];
        scores[0] = 20;
        scores[1] = 21;
        scores[2] = 22;
        for(std::size_t i = 0; i < 10; ++i) {
            std::cout << "scores [" << i << "]: " << scores[i] << std::endl;
        }
        std::cout << std::endl;
    };

    auto array_assign_with_loop = []() {
        std::cout << "Array assign with a loop" << std::endl;
        int scores[10];
        for(std::size_t i = 0; i < 10; ++i) {
            scores[i] = i * 10;
        }

        for(std::size_t i = 0; i < 10; ++i) {
            std::cout << "scores [" << i << "]: " << scores[i] << std::endl;
        }
        std::cout << std::endl;
    };

    auto array_declared_with_init = []() {
        std::cout << "Array declared with initialization" << std::endl;
        double salaries[5] = {12.7, 7.5, 13.2, 8.1, 9.3};
        for(std::size_t i=0; i<5; ++i) {
            std::cout << "salaries[" << i << "]: " << salaries[i] << std::endl;
        } 
        std::cout << std::endl;
    };

    auto array_partial_init_to_zero = []() {
        std::cout << "Array partial initialization to zero when not init" << std::endl;
        int families[5] {12, 7, 5};
        for(std::size_t i=0; i<5; ++i) {
            std::cout << "families[" << i << "]: " << families[i] << std::endl;
        }
        std::cout << std::endl;
    };

    auto omit_size_of_the_array = []() {
        std::cout << "Omit the size of the array at initialization" << std::endl;
        int class_sizes[] {10,12,15,11,18,17,23,56};
        for(auto value: class_sizes) {
            std::cout << "value: " << value << std::endl;
        }
        std::cout << std::endl;
    };

    auto read_only_array = []() {
        std::cout << "Read only array" << std::endl;
        int const birds[] = {10,12,15,11,18,17,23,56};
        // error: assignment of read-only location ‘birds[2]’
        // birds[2] = 8;
        std::cout << std::endl;
    };

    auto sum_up_array = []() {
        std::cout << "Sum up the array" << std::endl;
        int scores[] = {2,5,8,2,5,6,9};
        int sum = 0;
        for(int ele: scores) {
            sum += ele;
        }

        std::cout << "Score sum: " << sum << std::endl;
    };
    
    read_junk_data();
    read_junk_data_with_loop();
    array_assign();
    array_assign_with_loop();
    array_declared_with_init();
    array_partial_init_to_zero();
    omit_size_of_the_array();
    read_only_array();
    sum_up_array();

    return EXIT_SUCCESS;
}