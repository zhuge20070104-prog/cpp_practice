#ifndef _FREDRIC_DOG_H_
#define _FREDRIC_DOG_H_

#include <iostream>

class Dog {
    unsigned int m_age;

public:
    Dog(unsigned int age): m_age{age} {}

    void print_dog() const {
        std::cout << "Dog: " << m_age << '\n';
    }
};

#endif