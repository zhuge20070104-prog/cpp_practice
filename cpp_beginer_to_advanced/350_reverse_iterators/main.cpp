#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

template <typename Container>
void reverse_print(const Container& container) {
    auto rbegin_it {container.rbegin()};
    auto rend_it {container.rend()};
    while(rbegin_it != rend_it) {
        std::cout << *rbegin_it << " ";
        ++rbegin_it;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::vector<int> int_vector {1, 2, 3, 4, 5};
    reverse_print(int_vector);
    return EXIT_SUCCESS;    
}
