#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <functional>
#include "box_container.h"

char encrypt(const char& param) {
    return static_cast<char>(param + 8);
}

char decrypt(const char& param) {
    return static_cast<char>(param - 8);
}

class Decrypt {
public:
    char operator()(const char& c) {
        return static_cast<char>(c - 8);
    }
};

std::string& modify(std::string& src_param, const std::function<char(const char&)>& modifier) {
    for(std::size_t i{}; i<src_param.size(); ++i) {
        src_param[i] = modifier(src_param[i]);
    }
    return src_param;
}

int main(int argc, char* argv[]) {
    std::function<char(const char&)> modifier;
    modifier = encrypt;
    std::cout << "modifier('t'): " << modifier('t') << std::endl;

    modifier = decrypt;
    std::cout << "modifier('|'): " << modifier('|') << std::endl;

    Decrypt decrypt_functor;
    modifier = decrypt_functor;
    std::cout << "modifier('X'): " << modifier('X') << std::endl;

    modifier = [](const char& c) {
        return c + 8;
    };

    std::cout << "modifier('A'): " << modifier('A') << std::endl;

    // we can store function like entities in a container also using std::function
    BoxContainer<std::function<char(const char&)>> function_box;
    function_box.add(encrypt);
    function_box.add(decrypt);
    function_box.add(modifier);
    function_box.add(decrypt_functor);

    for(std::size_t i{}; i<function_box.size(); ++i) {
        std::cout << "function_box[" << i << "]: " << function_box.get_item(i)('A') << std::endl;
    }

    std::string str {"Hello"};
    std::cout << "modify(str, encrypt): " << modify(str, encrypt) << std::endl;
    std::cout << "modify(str, decrypt_functor): " << modify(str, decrypt_functor) << std::endl;
    std::cout << "modify(str, modifier): " << modify(str, modifier) << std::endl;

    return EXIT_SUCCESS;
}
