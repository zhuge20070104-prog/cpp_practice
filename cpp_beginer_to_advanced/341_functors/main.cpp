#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


class Encrypt {
public:
    char operator()(const char& c) {
        return static_cast<char>(c + 10);
    }
};

class Decrypt {
public:
    char operator()(const char& c) {
        return static_cast<char>(c - 10);
    }
};

char encrypt(const char& c) {
    return static_cast<char>(c + 8);
}

char decrypt(const char& c) {
    return static_cast<char>(c - 8);
}

template <typename Modifier>
std::string& modify(std::string& src_param, Modifier modifier) {
    for(std::size_t i{}; i<src_param.size(); ++i) {
        src_param[i] = modifier(src_param[i]);
    }
    return src_param;
}

int main(int argc, char* argv[]) {
   
    std::string str {"functors"};
    std::cout << "modify(str, encrypt): " << modify(str, encrypt) << std::endl;
    std::cout << "modify(str, decrypt): " << modify(str, decrypt) << std::endl;

    Encrypt encrypt_functor;
    Decrypt decrypt_functor;

    std::cout << "encrypt_functor('A'):" << encrypt_functor('A') << std::endl;
    std::cout << "decrypt_functor('Z'):" << decrypt_functor('Z') << std::endl;
   
    std::cout << "modify(str, encrypt_functor): " << modify(str, encrypt_functor) << std::endl;
    std::cout << "modify(str, decrypt_functor): " << modify(str, decrypt_functor) << std::endl;

    return EXIT_SUCCESS;
}
