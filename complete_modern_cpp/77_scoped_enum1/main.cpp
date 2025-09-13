#include <iostream>

enum Color {RED, GREEN, BLUE};
// 挖坑，两个重名了, redefinition 错误
// enum TrafficLight {RED, GREEN, BLUE};

void fill_color(Color const&  color) {
    if(color == RED) {
        std::cout << "Fill with red color\n"; 
    } else if(color == GREEN) {
        std::cout << "Fill with green color\n";
    } else if(color == BLUE) {
        std::cout << "Fill with blue color\n";
    }
} 



int main(int argc, char* argv[]) {
    fill_color(RED);
    fill_color(GREEN);
    // 不能直接传整型了，static_cast可以
    fill_color(static_cast<Color>(2));
    return EXIT_SUCCESS;
}