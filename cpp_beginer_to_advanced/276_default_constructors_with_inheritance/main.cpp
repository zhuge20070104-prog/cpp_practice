#include <iostream>

class Person {
public:
    Person() {
        std::cout << "BUILDING PERSON\n";
    }
};

class Engineer: public Person {
public:
    Engineer() {
        std::cout << "BUILDING ENGINEER\n";
    }
};

class CivilEngineer: public Engineer {
public:
    CivilEngineer() {
        std::cout << "BUILDING CIVIL ENGINEER\n";
    }
};

int main(int argc, char* argv[]) {
    CivilEngineer ce1;
    return EXIT_SUCCESS;
}