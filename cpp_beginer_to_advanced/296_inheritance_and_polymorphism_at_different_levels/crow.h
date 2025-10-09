#ifndef _FREDRIC_CROW_H_
#define _FREDRIC_CROW_H_

#include <string_view>
#include <string>
#include <iostream>
#include "bird.h"

class Crow: public Bird {
public:
    Crow() = default;
    Crow(std::string_view wing_color, std::string_view desc):
        Bird{wing_color, desc} {}
    virtual ~Crow() = default;

    virtual void caw() const {
        std::cout << "Crow is cawing: " << m_description << '\n';
    }

    virtual void breathe() const override {
        std::cout << "Crow is breathing: " << m_description << '\n';
    }

    virtual void stream_insert(std::ostream& os) const override {
        os << "Crow: [Description: " << m_description << ", Wing Color: " << m_wing_color << "]";
    }
};
#endif