#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include "box_container.h"

void populate_box(BoxContainer<int>& box, int modifier) {
    for(int i{0}; i<20; ++i) {
        box.add((i+1) * modifier);
    }
}

BoxContainer<int> make_box(int modifier) {
    BoxContainer<int> local_box(20);
    populate_box(local_box, modifier);
    return local_box;
}

template <typename T>
void swap_values(T& a, T& b) {
    T temp {std::move(a)};
    a = std::move(b);
    b = std::move(temp);
}


int main(int argc, char* argv[]) {
    BoxContainer<int> int_box1;
    populate_box(int_box1, 189);
    BoxContainer<int> int_box2;
    populate_box(int_box2, 101);

    std::cout << "Before swap: " << std::endl;
    std::cout << "int_box1: " << int_box1 << std::endl;
    std::cout << "int_box2: " << int_box2 << std::endl;

    swap_values(int_box1, int_box2);

    std::cout << "After swap: " << std::endl;
    std::cout << "int_box1: " << int_box1 << std::endl;
    std::cout << "int_box2: " << int_box2 << std::endl;
    
    return EXIT_SUCCESS;
}
