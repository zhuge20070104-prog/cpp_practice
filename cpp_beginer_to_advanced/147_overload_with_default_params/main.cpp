#include <iostream>

void print_age(int age=33);

int main()
{
    print_age();
    return EXIT_SUCCESS;
}

void print_age(int age) {
    std::cout << "Your age is(int version): " << age << std::endl;
}
