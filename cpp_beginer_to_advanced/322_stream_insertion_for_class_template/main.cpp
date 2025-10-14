#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"


int main(int argc, char* argv[]) {
    BoxContainer<int> int_box;
    int_box.add(1);
    int_box.add(2);
    std::cout << "int_box: " << int_box << std::endl;
    return EXIT_SUCCESS;
}
