#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for(const auto& element: vec) {
        os << element << " ";
    }
    os << '\n';
    return os;
}

int main(int argc, char* argv[]) {
    std::vector<int> num_vector {5, 1, 8, 2, 6, 3 ,4};
    std::cout << num_vector;

    if(std::ranges::find(num_vector.cbegin(), num_vector.cend(), 7) != num_vector.cend()) {
        std::cout << "num_vector contains 7" << std::endl;
    } else {
        std::cout << "num_vector does not contain 7" << std::endl;
    }

    std::vector<int> num_vector_dest(num_vector.size()); 
    std::ranges::copy(num_vector.cbegin(), num_vector.cend(), num_vector_dest.begin());
    std::cout << num_vector;
    std::cout << num_vector_dest;

    std::ranges::replace(num_vector.begin(), num_vector.end(), 1, 9);

    std::cout << num_vector;

    auto it_begin {num_vector_dest.begin()};
    auto it_end {num_vector_dest.end()};

    while(it_end-- != it_begin) {
        std::cout << "reversing +++" << std::endl;
        std::ranges::reverse(num_vector_dest);
    }

    std::cout << "after reversing: " << std::endl;
    std::cout << num_vector_dest;

    std::ranges::sort(num_vector);
    std::cout << num_vector;

    return EXIT_SUCCESS;
}