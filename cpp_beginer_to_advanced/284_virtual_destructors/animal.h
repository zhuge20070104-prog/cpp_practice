#ifndef _FREDRIC_ANIMAL_H
#define _FREDRIC_ANIMAL_H

#include <iostream>
#include <string>
#include <string_view>

class Animal {
public:
    Animal() = default;
    Animal(std::string_view desc): m_description(desc) {}
    virtual ~Animal() {
        std::cout << "Animal destructor called"<< std::endl;
    }

    virtual void breathe() const {
        std::cout << "Animal is breathing:" << m_description << std::endl;
    }
private:
    std::string m_description{};
};

#endif