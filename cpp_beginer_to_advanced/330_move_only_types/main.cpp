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
    BoxContainer<int> box1(20);
    BoxContainer<int> box2(20);
    populate_box(box2, 2);

    box1 = std::move(box2);
    std::cout << "box1: " << box1 << std::endl;
    std::cout << "box2: " << box2 << std::endl;

    
    return EXIT_SUCCESS;
}
