#ifndef _FREDRIC_ANIMAL_H_
#define _FREDRIC_ANIMAL_H_

#include <iostream>
#include <string_view>
#include <string>
#include "stream_insertable.h"

class Animal: public StreamInsertable {
public:
    Animal() = default;
    Animal(std::string_view desc): m_description{desc} {}

    virtual ~Animal() = default;

    virtual void breathe() const {
        std::cout << "Animal is breathing: " << m_description << '\n';
    }

protected:
    std::string m_description {};
};

#endif