#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

template <typename T>
using compare_T = bool (*) (const T&, const T&);

template <typename T>
T get_best(const std::vector<T>& items, compare_T<T> comparator) {
    T best{items[0]};
    for(std::size_t i{}; i<items.size(); ++i) {
        if(comparator(items[i], best)) {
            best = items[i];
        }
    }
    return best;
}

bool larger_in_size(const std::string& lhs, const std::string& rhs) {
    return lhs.size() > rhs.size();
}

bool lexographically_greater(const std::string& lhs, const std::string& rhs) {
    return lhs > rhs;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& sentences) {
    os << "[";
    for(std::size_t i{}; i<sentences.size(); ++i) {
        os << sentences[i] << " ";
    }
    os << "]";
    return os;
}

bool larger_int(const int& lhs, const int& rhs) {
    return lhs > rhs;
}

template <typename T>
bool smaller(const T& lhs, const T& rhs) {
    return lhs < rhs;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> quote {"The", "dog", "is", "an", "animal"};
    std::cout << "get_best(quote, larger_in_size): " << get_best(quote, larger_in_size) << std::endl;
    std::cout << "get_best(quote, lexographically_greater): " << get_best(quote, lexographically_greater) << std::endl;

    std::vector<int> numbers {2, 89, 12, 72};
    std::cout << "get_best(numbers, larger_int): " << get_best(numbers, larger_int) << std::endl;
    std::cout << "get_best(numbers, smaller): " << get_best(numbers, smaller) << std::endl;

    return EXIT_SUCCESS;
}
