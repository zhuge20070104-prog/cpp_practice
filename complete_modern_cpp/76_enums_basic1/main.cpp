#include <iostream>

#define RED 0
int const GREEN = 1;

void fill_color(int color) {
    if(color == 0) {
        std::cout << "Fill with red color\n"; 
    } else if(color == 1) {
        std::cout << "Fill with green color\n";
    }
} 

int main(int argc, char* argv[]) {
    fill_color(RED);
    fill_color(GREEN);
    // 函数内部并不知道如何处理6， 任何整型值都可以传
    fill_color(6);
    return EXIT_SUCCESS;
}