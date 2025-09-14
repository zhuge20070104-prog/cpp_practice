#include <iostream>
#include <string>


class Size {
private:
    int integer {};  // 4 -->  padding to 8
    double floating_point {}; // 8 --> original 8
    char character {}; // 1 --> padding to 8

    // 3 * 8 = 24
};

int main(int argc, char* argv[]) {
   
    Size sz;
    std::cout << "sizeof(sz): " << sizeof(sz) << std::endl;
    
    return EXIT_SUCCESS;
}

