#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


template <typename Container>
void print_subset(const Container& container, std::size_t start_offset, std::size_t end_offset) {
    auto begin {container.begin() + start_offset};
    auto end {container.end() - end_offset};
    while(begin != end) {
        std::cout << *begin << " ";
        ++begin;
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::vector<int> int_vector {1, 2, 3, 4, 5};
    print_subset(int_vector, 1, 1);    
    return EXIT_SUCCESS;    
}
