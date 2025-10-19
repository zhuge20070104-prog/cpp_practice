#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

template <typename Iterator>
void print(Iterator begin, Iterator end) {
    while(begin != end) {
        std::cout << *begin << " ";
        ++begin;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> string_vector {"This", "is", "a", "string", "vector"};
    std::cout << "string_vector[3]: " << string_vector[3] << std::endl;
    print(string_vector.begin(), string_vector.end());

    // () syntax creates a vector of 10 items with each value 4
    std::vector<int> int_vector1(10, 4);
    // {} syntax creates a vector of the values specified
    std::vector<int> int_vector2 {10, 4};
    print(int_vector1.begin(), int_vector1.end());
    print(int_vector2.begin(), int_vector2.end());

    std::cout << "string_vector.at(3): " << string_vector.at(3) << std::endl;
    std::cout << "string_vector.front(): " << string_vector.front() << std::endl;
    std::cout << "string_vector.back(): " << string_vector.back() << std::endl;

    print(string_vector.data(), string_vector.data() + string_vector.size());

    int_vector2.push_back(40);
    print(int_vector2.begin(), int_vector2.end());
    
    string_vector.pop_back();
    print(string_vector.begin(), string_vector.end());

    return EXIT_SUCCESS;    
}
