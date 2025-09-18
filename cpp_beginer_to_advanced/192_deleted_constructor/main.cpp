#include <iostream>
#include <string_view>

class Man {
    unsigned int m_age {};

public:
    Man() = delete;

    explicit Man(unsigned int age) : m_age(age) {}
};

int main(int argc, char* argv[]) {
   
    // Man man1;
    Man man2 {30};

    return EXIT_SUCCESS;
}

