#include <iostream>

class Parent {
protected:
    int age {0};

public:
    void print_age() {
        std::cout << "Parent age: " << age << std::endl;
    }
};


class Child: public Parent {
public:
    void print_age() {
        std::cout << "Child age: " << age << std::endl;
        std::cout << "Parent's age too: " << Parent::age << std::endl;
    }

protected:
    int age {1};
};

int main(int argc, char* argv[]) {
    Child c1;
    c1.print_age();

    c1.Parent::print_age();
    return EXIT_SUCCESS;
}