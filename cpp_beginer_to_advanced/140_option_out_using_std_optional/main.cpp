#include <iostream>
#include <optional>

std::optional<std::size_t> find_char_v2(std::string const& str, char c) {
    // If found set the return index, else return an empty std::optional
    for(std::size_t i=0; i<str.size(); ++i) {
        if(str.data()[i] == c) {
            return i;
        }
    }
    // or std::nullopt
    return {};
}

std::optional<std::size_t> find_char_v3(std::string const& str, std::optional<char> c = std::nullopt) {
    // If c is specified, find it else just find 'z'
    char char_to_find = c.value_or('z');
    for(std::size_t i=0; i<str.size(); ++i) {
        if(str.data()[i] == char_to_find) {
            return i;
        }
    }
    // or std::nullopt
    return {};
}


int main()
{
    std::string str1 = "Hello world in C++ 17";
    char c{'c'};
    std::optional<std::size_t> result = find_char_v2(str1, c);
    if(result.has_value()) {
        std::cout << "Found our character at index: " << result.value() << std::endl;
    } else {
        std::cout << "Didn't find our character" << std::endl;
    }

    str1 = "Hello worldz in C++17";
    std::optional<std::size_t> result1 = find_char_v3(str1, 'o');
    if(result1.has_value()) {
        std::cout << "Found character 'o' at index: " << result1.value() << std::endl;
    } else {
        std::cout << "Could not find character 'o' in the string: " << str1 << std::endl;
    }

    return 0;
}
