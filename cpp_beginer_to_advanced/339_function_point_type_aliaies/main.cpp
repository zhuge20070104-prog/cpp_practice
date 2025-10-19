#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

char encrypt(const char& param) {
    return static_cast<char>(param + 10);
}

char decrypt(const char& param) {
    return static_cast<char>(param - 10);
}

void modify(std::string& input_str, char (*modifier)(const char&)) {
    for(std::size_t i{}; i<input_str.size(); ++i) {
        input_str[i] = modifier(input_str[i]);
    }
}

void modify(std::vector<std::string>& sentences, char (*modifier)(const char&)) {
    for(std::size_t i{}; i<sentences.size(); ++i) {
        for(std::size_t j{}; j<sentences[i].size(); ++j) {
            sentences[i][j] = modifier(sentences[i][j]);
        }
    }
}

using str_comparator = bool(*)(const std::string&, const std::string&);

std::string get_best(const std::vector<std::string>& sentences, str_comparator comparator) {
    std::string best{sentences[0]};

    for(std::size_t i{}; i<sentences.size(); ++i) {
        if(comparator(sentences[i], best)) {
            best = sentences[i];
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

int main(int argc, char* argv[]) {
    std::vector<std::string> quote {"The", "dog", "is", "an", "animal"};
    modify(quote, encrypt);
    std::cout << "quote: " << quote << std::endl;
    modify(quote, decrypt);
    std::cout << "quote: " << quote << std::endl;

    std::cout << "get_best(quote, larger_in_size): " << get_best(quote, larger_in_size) << std::endl;
    std::cout << "get_best(quote, lexographically_greater): " << get_best(quote, lexographically_greater) << std::endl;
    return EXIT_SUCCESS;
}
