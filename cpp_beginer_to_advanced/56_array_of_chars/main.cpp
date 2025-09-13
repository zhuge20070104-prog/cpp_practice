#include <iostream>
#include <algorithm>


int main(int argc, char* argv[]) {

    auto null_character_space = [] () {
        // 必须为null character 分配空间
        std::cout << "null character space" << std::endl;
        // char message[5] = {"Hello"};
        char message[6] = {"Hello"};
        std::cout << "message: " << message << std::endl;
        std::cout << std::endl;
    };

    char message[6] = {"Hello"};
    auto print_data_by_char = [&message]() {
        std::cout << "message: ";
        for(auto c: message) {
            std::cout << c;
        }
        std::cout << std::endl << std::endl;
    };

    auto change_char_in_array = [&message]() {
        message[1] = 'a';
        std::cout << "message: ";
        for(auto c: message) {
            std::cout << c;
        }
        std::cout << std::endl << std::endl;
    };

    auto c_string1 = []() {
        char message[] = {'H', 'e', 'l', 'l', 'o', '\0'};
        std::cout << "message: " << message << std::endl;
        std::cout << "sizeof(message)： " << sizeof(message) << std::endl;
        std::cout << std::endl;
    }; 

    auto c_string2 = []() {
        std::cout << "default null character" << std::endl;
        char message[6] = {'H', 'e', 'l', 'l', 'o'};
        std::cout << "message: " << message << std::endl;
        std::cout << "sizeof(message): " << sizeof(message) << std::endl;
        std::cout << std::endl;
    };

    auto not_a_c_string = []() {
        std::cout << "without null character, not a c-string" << std::endl;
        char message[] = {'H', 'e', 'l', 'l', 'o'};
        std::cout << "message: " << message << std::endl;
        std::cout << "sizeof(message): " << sizeof(message) << std::endl;
        std::cout << std::endl;
    };

    auto string_literal = []() {
        std::cout << "string literal without size, valid c-string" << std::endl;
        char message[] = {"Hello"};
        std::cout << "message: " << message << std::endl;
        std::cout << "sizeof(message): " << sizeof(message) << std::endl;
        std::cout << std::endl;
    };

    auto int_array_print = []() {
        std::cout << "array only print out address" << std::endl;
        int numbers[] = {1, 2, 3, 4, 5};
        // belows print out array address instead of the content of the array
        // std::cout << "numbers: " << numbers << std::endl;
        std::for_each(std::begin(numbers), std::end(numbers), [](int const& val){
            std::cout << "value: " << val << std::endl;
        });
        std::cout << std::endl;
    };

    null_character_space();
    print_data_by_char();
    change_char_in_array();
    c_string1();
    c_string2();
    not_a_c_string();
    string_literal();
    int_array_print();

    return EXIT_SUCCESS;
}