#include <exception>
#include <iostream>
#include <string>
#include <string_view>

char encrypt(const char& param) {
    return static_cast<char>(param + 10);
}

char decrypt(const char& param) {
    return static_cast<char>(param - 10);
}

std::string modify(const std::string& str_param, char (*modifier)(const char&)) {
    std::string result(str_param.size(), 'c');  // 创建副本
    for(std::size_t i{}; i<result.size(); ++i) {
        result[i] = modifier(str_param[i]);
    }
    return result;
}

int main(int argc, char* argv[]) {
    std::string str {"Hello"};
    auto encoded_str = modify(str, encrypt);
    auto decoded_str = modify(encoded_str, decrypt);
    std::cout << "encoded_str: " << encoded_str << std::endl;
    std::cout << "decoded_str: " << decoded_str << std::endl;
    
    return EXIT_SUCCESS;
}
