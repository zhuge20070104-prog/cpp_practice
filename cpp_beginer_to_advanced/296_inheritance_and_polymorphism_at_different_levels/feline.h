#ifndef _FREDRIC_FELINE_H_
#define _FREDRIC_FELINE_H_

#include "animal.h"

class Feline: public Animal {
public:
    Feline() = default;
    Feline(std::string_view fur_style, std::string_view desc):
        Animal{desc}, m_fur_style{fur_style} {}
    virtual ~Feline() = default;

    virtual void run() const {
        std::cout << "Feline is running: " << m_fur_style << '\n';
    }

    std::string m_fur_style {};
};

#endif