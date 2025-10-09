#ifndef _FREDRIC_BIRD_H_
#define _FREDRIC_BIRD_H_

#include "animal.h"

class Bird: public Animal {
public:
    Bird() = default;
    Bird(std::string_view wing_color, std::string_view desc):
        Animal{desc}, m_wing_color{wing_color} {}
    virtual ~Bird() = default;

    virtual void fly() const {
        std::cout << "Bird is flying: " << m_description << '\n';
    }

protected:
    std::string m_wing_color {};
};

#endif