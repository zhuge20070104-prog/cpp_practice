#include <iostream>

int free_standing_variable {};

void do_something() {
    std::cout << "do_something() called" << '\n';
}

struct Point {
    double m_x{};
    double m_y{};
};

class Person {
public:
    explicit Person(int age): m_age{age} {}

private:
    int m_age{};
};


int main(int argc, char* argv[]) {
    std::cout << "free_standing_variable: " << free_standing_variable << '\n';
    Point point {};
    Person person {20};
    
    return EXIT_SUCCESS;
}

