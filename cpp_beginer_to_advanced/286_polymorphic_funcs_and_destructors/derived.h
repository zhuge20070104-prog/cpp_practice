#ifndef _FREDRIC_DERIVED_H
#define _FREDRIC_DERIVED_H

#include "base.h"

class Derived: public Base {
public:
    Derived() {
        std::cout << "Derived constructor called" << std::endl;
    }
    
    virtual ~Derived() {
        std::cout << "Derived destructor called" << std::endl;
    }

    virtual void setup() override {
        std::cout << "Derived setup called" << std::endl;
        m_value = 100;
    }

    virtual void cleanup() override {
        std::cout << "Derived cleanup called" << std::endl;
    }
};

#endif