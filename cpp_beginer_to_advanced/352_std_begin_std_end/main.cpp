#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


int main(int argc, char* argv[]) {
    int raw_array[] {1, 2, 3, 4, 5};
    std::vector<int> int_vector {11, 22, 33, 44, 55};

    for(auto iter=std::begin(raw_array); iter != std::end(raw_array); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    for(auto iter=std::begin(int_vector); iter != std::end(int_vector); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;    
}
