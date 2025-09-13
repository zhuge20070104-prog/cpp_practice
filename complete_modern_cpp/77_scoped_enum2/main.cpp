#include <iostream>

enum class Color {RED, GREEN, BLUE};
// 解决重名问题
enum class TrafficLight: char {RED='c', GREEN, BLUE};

void fill_color(Color const&  color) {
    if(color == Color::RED) {
        std::cout << "Fill with red color\n"; 
    } else if(color == Color::GREEN) {
        std::cout << "Fill with green color\n";
    } else if(color == Color::BLUE) {
        std::cout << "Fill with blue color\n";
    }
} 



int main(int argc, char* argv[]) {
    fill_color(Color::RED);
    fill_color(Color::GREEN);
    // 不能直接传整型了，static_cast可以
    fill_color(static_cast<Color>(2));

    std::cout << "Blue value is: " << static_cast<int>(Color::BLUE) << std::endl;
    std::cout << "Traffic green value is: " << static_cast<int>(TrafficLight::GREEN) << std::endl;
    return EXIT_SUCCESS;
}