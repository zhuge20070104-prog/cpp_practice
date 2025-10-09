#ifndef _FREDRIC_DOG_H_
#define _FREDRIC_DOG_H_

#include "feline.h"

class Dog: public Feline {
public:
    Dog() = default;
    Dog(std::string_view fur_style, std::string_view desc):
        Feline{fur_style, desc} {}
    virtual ~Dog() = default;

    virtual void bark() const {
        std::cout << "Dog is barking: " << '\n';
    }

    virtual void breathe() const override {
        std::cout << "Dog is breathing: " << m_fur_style << '\n';
    }

    virtual void run() const override {
        std::cout << "Dog is running: " << m_fur_style << '\n';
    }

    virtual void stream_insert(std::ostream& os) const override {
        os << "Dog: [Description: " << m_description << ", Fur Style: " << m_fur_style << "]";
    }
};
#endif