#include <iostream>

void say_age(int age) {
    ++age;
    std::cout << "Hello, you are " << age << " years old! &age: " << &age << std::endl;
}

int main(int argc, char* argv[]) {
    int age{23};
    std::cout << "age (before call): " << age << " &age: " << &age << std::endl;
    say_age(age);
    std::cout << "age (after call): " << age << " &age: " << &age << std::endl;
    return EXIT_SUCCESS;
}