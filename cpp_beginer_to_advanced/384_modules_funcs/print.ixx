module;

#include <iostream>
#include <string_view>


export module print;

export void print_name(std::string_view name) {
    std::cout << "Name: " << name << '\n';
}