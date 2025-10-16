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


int main(int argc, char* argv[]) {
    BoxContainer<int> int_box_array[2];
    for(int i{0}; i<2; ++i) {
        int_box_array[i] = make_box(i+281);
    }

    std::cout << "int_box_array[0]: " << int_box_array[0] << std::endl;
    std::cout << "int_box_array[1]: " << int_box_array[1] << std::endl;
    
    return EXIT_SUCCESS;
}
