#include <iostream>
#include <string>

// Ambiguous calls
void say_my_name(std::string const& name) {
    std::cout << "Your name is (ref): " << name << std::endl;
}

void say_my_name(std::string name) {
    std::cout << "Your name is (non ref): " << name << std::endl;
}

// Implicit conversion with reference
double max(double a, double b) {
    std::cout << "double max called" << std::endl;
    return (a>b) ? a: b;
}

int const& max(int const& a, int const& b) {
    std::cout << "int max called" << std::endl;
    return (a>b)? a: b;
}


int main()
{
    char a{6};
    char b{9};
    auto result = max(a, b);
    std::cout << "result: " << static_cast<int>(result) << std::endl;
    // say_my_name("Fredric");
    return 0;
}
