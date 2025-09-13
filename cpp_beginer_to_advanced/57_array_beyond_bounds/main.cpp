#include <iostream>
#include <algorithm>


int main(int argc, char* argv[]) {

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    auto read_beyond_bounds = [&numbers]() {
        //Read beyond bounds : Will read garbage or crash your program
        std::cout << "read beyond bounds" << std::endl;
        std::cout << "numbers[12]: " << numbers[12] << std::endl;
    }; 

    auto write_beyond_bounds = [&numbers]() {
        //Write beyond bounds. The compiler allows it. But you don't own 
	    //the memory at index 12, so other programs may modify it and your
	    //program may read bogus data at a later time. Or you can even
	    //corrupt data used by other parts of your program
        std::cout << "write beyond bounds" << std::endl;
        numbers[129] = 1000;
        std::cout << "numbers[129]: " << numbers[129] << std::endl;
    };

    read_beyond_bounds();
    write_beyond_bounds();
    std::cout << "program ending..." << std::endl;

    return EXIT_SUCCESS;
}