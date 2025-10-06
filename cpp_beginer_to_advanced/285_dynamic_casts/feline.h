#ifndef _FREDRIC_FELINE_H
#define _FREDRIC_FELINE_H

#include <iostream>
#include <string>
#include <string_view>
#include "animal.h"

class Feline: public Animal {
public:
    Feline() = default;
    Feline(std::string_view fur_style, std::string_view desc): Animal(desc), m_fur_style(fur_style) {}
    virtual ~Feline() {
    }

    virtual void run() const {
        std::cout << "Feline is running:" << m_fur_style << std::endl;
    }

    void do_feline_thing() const {
        std::cout << "Feline is doing something" << std::endl;
    }
protected:
    std::string m_fur_style{};
};

#endif