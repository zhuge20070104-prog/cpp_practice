#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <functional>


template <typename T, typename Comparator>
T get_best(const std::vector<T>& sentence, Comparator comparator) {
    T best{sentence[0]};
    for(std::size_t i{}; i<sentence.size(); ++i) {
        if(comparator(sentence[i], best)) {
            best = sentence[i];
        }
    }
    return best;
}

template <typename T>
bool custom_greater(const T& lhs, const T& rhs) {
    return lhs > rhs;
}

template <typename T>
class Greater {
public:
    bool operator()(const T& lhs, const T& rhs) {
        return lhs > rhs;
    }
};

std::plus<int> adder;
std::greater<int> compare_greater;
std::minus<int> subtractor;
std::greater<std::string> string_greater;


int main(int argc, char* argv[]) {
    std::cout << "adder(2, 3): " << adder(2, 3) << std::endl;
    std::cout << "compare_greater(6, 3): " << compare_greater(6, 3) << std::endl;
    std::cout << "subtractor(10, 6): " << subtractor(10, 6) << std::endl;
   
    std::vector<std::string> quote {"The", "dog", "is", "an", "animal"};

    std::cout << "get_best(quote, custom_greater<std::string>): " << get_best(quote, custom_greater<std::string>) << std::endl;
    std::cout << "get_best(quote, string_greater): " << get_best(quote, string_greater) << std::endl;

    std::cout << "get_best(quote, std::greater<std::string>{}): " << get_best(quote, std::greater<std::string>{}) << std::endl;
    Greater<std::string> custom_functor_greater;
    std::cout << "get_best(quote, custom_functor_greater): " << get_best(quote, custom_functor_greater) << std::endl;

    return EXIT_SUCCESS;
}
