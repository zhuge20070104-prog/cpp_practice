#ifndef _FREDRIC_PIGEON_H_
#define _FREDRIC_PIGEON_H_

#include "bird.h"
#include <string_view>
#include <string>
#include <iostream>

class Pigeon: public Bird {
public:
    Pigeon() = default;
    Pigeon(std::string_view wing_color, std::string_view desc):
        Bird{wing_color, desc} {}
    virtual ~Pigeon() = default;

    virtual void coo() const {
        std::cout << "Pigeon is cooing: " << m_description << '\n';
    }

    virtual void breathe() const override {
        std::cout << "Pigeon is breathing: " << m_description << '\n';
    }

    virtual void stream_insert(std::ostream& os) const override {
        os << "Pigeon: [Description: " << m_description << ", Wing Color: " << m_wing_color << "]";
    }

};

#endif