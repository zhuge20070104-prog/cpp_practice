#include <iostream>


int main(int argc, char* argv[]) {
    // 整型 条件
    int condition {-5};

    bool bool_conditoin = condition;
    
    if(bool_conditoin) {
        // 和0不一样
        std::cout << "We have a " << bool_conditoin << " in our variable" << std::endl;
    } else {
        // 0
        std::cout << "We have " << bool_conditoin << " in our variable" << std::endl;
    }
    return EXIT_SUCCESS;
}