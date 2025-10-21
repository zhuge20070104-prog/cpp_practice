#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


int main(int argc, char* argv[]) {
    std::vector<int> int_vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto const_iter {int_vector.cbegin()};
    while(const_iter != int_vector.cend()) {
        std::cout << *const_iter << " ";
        ++const_iter;
    }
    std::cout << std::endl;

    const std::vector<int> const_vector {1, 2, 3};
    auto const_iter1 {const_vector.begin()};
    while(const_iter1 != const_vector.end()) {
        std::cout << *const_iter1 << " ";
        ++const_iter1;
    }

    std::cout << std::endl;
    return EXIT_SUCCESS;    
}
