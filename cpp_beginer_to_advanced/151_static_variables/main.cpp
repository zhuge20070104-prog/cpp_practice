#include <iostream>

// global variable - alive and accessible throughout the program
std::size_t total_dogs {3000};

unsigned int add_student() {
    static unsigned int student_count {0};
    std::cout << "student_count: " << student_count << '\n';
    ++student_count;

    ++total_dogs;
    return student_count;
}

int main(int argc, char* argv[]) {

    for(std::size_t i{0}; i<10; ++i) {
        add_student();
    }

    std::cout << "total_dogs: " << total_dogs << '\n';
    
    return EXIT_SUCCESS;
}