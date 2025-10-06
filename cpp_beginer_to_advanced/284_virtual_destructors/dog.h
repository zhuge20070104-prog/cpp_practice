#ifndef _FREDRIC_DOG_H
#define _FREDRIC_DOG_H

#include <iostream>
#include <string>
#include <string_view>
#include "feline.h"

class Dog: public Feline {
public:
    Dog() = default;
    Dog(std::string_view fur_style, std::string_view desc): Feline(fur_style, desc) {}
    virtual ~Dog() {
        std::cout << "Dog destructor called"<< std::endl;
    }

    virtual void bark() const {
        std::cout << "Dog is barking"<< std::endl;
    }

    virtual void breathe() const override {
        std::cout << "Dog is breathing:" << m_fur_style << std::endl;
    }
    
    virtual void run() const override {
        std::cout << "Dog is running:" << m_fur_style << std::endl;
    }
};

#endif