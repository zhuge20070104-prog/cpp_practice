#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <functional>

void modify(std::string& input_str, char (*modifier)(const char&)) {
    for(std::size_t i{}; i<input_str.size(); ++i) {
        input_str[i] = modifier(input_str[i]);
    }
}

int main(int argc, char* argv[]) {
    std::string str {"Hello World"};

    auto encrypt {
        [](const char& param) {
            return static_cast<char>(param + 8);
        }
    };

    auto decrypt {
        [](const char& param) {
            return static_cast<char>(param - 8);
        }
    };

    modify(str, encrypt);
    std::cout << "encrypt(str): " << str << std::endl;
    modify(str, decrypt);
    std::cout << "decrypt(str): " << str << std::endl;

    modify(str, [](const char& param) {
        return static_cast<char>(param + 8);
    });
    std::cout << "lambda encrypt(str): " << str << std::endl;
    return EXIT_SUCCESS;    
}
