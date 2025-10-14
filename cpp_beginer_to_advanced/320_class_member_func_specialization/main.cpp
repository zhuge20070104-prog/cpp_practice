#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"

int main(int argc, char* argv[]) {
    BoxContainer<int> int_box;
    int_box.add(3);
    int_box.add(6);
    int_box.add(2);
    int_box.add(5);

    std::cout << "int_box: " << int_box << std::endl;
    std::cout << "int_box.get_max(): " << int_box.get_max() << std::endl;

    char c1[] {"hello"};
    char c2[] {"there"};
    char c3[] {"world"};

    BoxContainer<char*> char_box;
    char_box.add(c1);
    char_box.add(c2);
    char_box.add(c3);

    std::cout << "char_box: " << char_box << std::endl;
    std::cout << "char_box.get_max(): " << char_box.get_max() << std::endl;

    return EXIT_SUCCESS;
}
