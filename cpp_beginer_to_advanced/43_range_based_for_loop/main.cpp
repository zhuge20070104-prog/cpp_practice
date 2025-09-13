#include <iostream>


int main(int argc, char* argv[]) {
    int bag_of_values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto common_for_loop = [&bag_of_values]() {
        for(std::size_t i = 0; i < 10; ++i) {
            std::cout << "value: " << bag_of_values[i] << std::endl;
        }
    }; 

    auto range_based_for = [&bag_of_values]() {
        for(int value: bag_of_values) {
            std::cout << "value: " << value << std::endl;
        }
    };

    auto range_based_for_inplace = [&bag_of_values]() {
        for(int value: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) {
            std::cout << "value: " << value << std::endl;
        }
    };

    auto range_based_auto_deduct = [&bag_of_values]() {
        for(auto value: bag_of_values) {
            std::cout << "value: " << value << std::endl;
        }
    };

    common_for_loop();
    std::cout << std::endl;
    range_based_for();
    std::cout << std::endl;
    range_based_for_inplace();
    std::cout << std::endl;
    range_based_auto_deduct();
    std::cout << std::endl;

    return EXIT_SUCCESS;
}