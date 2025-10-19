#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <experimental/array>


template <typename Iterator>
void print(Iterator begin, Iterator end) {
    while(begin != end) {
        std::cout << *begin << " ";
        ++begin;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::array<int, 2> array_junk {};
    print(array_junk.begin(), array_junk.end());

    std::array<int, 5> array1 {1, 2, 3, 4, 5};
    print(array1.begin(), array1.end());

    // auto type and size deduction
    std::array array2 {2, 4, 8, 10};
    print(array2.begin(), array2.end());

    // auto type and size deduction
    auto make_array {std::experimental::make_array(1, 2, 3)};
    print(make_array.begin(), make_array.end());

    std::array<int, 5> array3 {};
    array3[0] = 2;
    array3[1] = 4;
    array3[2] = 8;

    std::cout << "array3.at(1): " << array3.at(1) << std::endl;
    std::cout << "array3.front(): " << array3.front() << std::endl;
    std::cout << "array3.back(): " << array3.back() << std::endl;

    print(array3.data(), array3.data() + array3.size());
    
    return EXIT_SUCCESS;    
}
