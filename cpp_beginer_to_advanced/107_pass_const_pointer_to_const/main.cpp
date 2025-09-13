#include <iostream>

// 全局的dog_count 变量
int dog_count = 2;

void say_age(int const* const age);

int main(int argc, char* argv[]) {
    int age {23};
    std::cout << "age (before call): " << age << " &age: " << &age << std::endl;
    say_age(&age);
    std::cout << "age (after call): " << age << " &age: " << &age << std::endl;   
    return EXIT_SUCCESS;
}

void say_age(int const* const age) {
    // ++(*age);
    std::cout << "Hello, you are " << *age << " years old! &age: " << age << std::endl;
    // age = &dog_count;
}