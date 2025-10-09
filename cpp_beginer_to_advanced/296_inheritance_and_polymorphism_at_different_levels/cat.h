#ifndef _FREDRIC_CAT_H_
#define _FREDRIC_CAT_H_

#include <string_view>
#include <string>
#include <iostream>
#include "feline.h"

class Cat: public Feline {
public:
    Cat() = default;
    Cat(std::string_view fur_style, std::string_view desc):
        Feline{fur_style, desc} {}
    virtual ~Cat() = default;

    virtual void miaw() const {
        std::cout << "Cat is miawing: " << '\n';
    }

    virtual void breathe() const override {
        std::cout << "Cat is breathing: " << m_fur_style << '\n';
    }

    virtual void run() const override {
        std::cout << "Cat is running: " << m_fur_style << '\n';
    }

    virtual void stream_insert(std::ostream& os) const override {
        os << "Cat: [Description: " << m_description << ", Fur Style: " << m_fur_style << "]";
    }
};
#endif