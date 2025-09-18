#include <iostream>
#include <initializer_list>
#include <cassert>

struct Point {
    double x {};
    double y {};
};


int main(int argc, char* argv[]) {
    Point p1 {2.8, 9.2};
    int scores [] {2, 3, 9, 5, 7};

   
    std::cout << "x: " << p1.x << ", y: " << p1.y << std::endl;
    

    for(const auto& score: scores) {
        std::cout << "score: " << score << std::endl;
    }

    return EXIT_SUCCESS;
}

