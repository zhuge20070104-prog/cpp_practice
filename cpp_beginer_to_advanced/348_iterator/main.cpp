#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>


template <typename Collection>
void print(const Collection& collection) {
    auto iter {collection.begin()};
    while(iter != collection.end()) {
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::vector<int> int_vector {1, 2, 3, 4};
    std::array<int, 4> int_array {20, 30, 10, 11};
    
    std::vector<int>::iterator iter_begin {int_vector.begin()};
    std::vector<int>::iterator iter_end {int_vector.end()};

    // Works like pointer arithmetic
    std::cout << std::boolalpha;
    std::cout << *iter_begin << std::endl;
    std::cout << *(iter_begin + 1) << std::endl;

    std::cout << (iter_begin == iter_end) << std::endl;

    std::cout << *iter_end << std::endl;

    print(int_vector);
    print(int_array);

    return EXIT_SUCCESS;    
}
