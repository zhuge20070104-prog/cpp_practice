#ifndef _FREDRIC_BASE_H
#define _FREDRIC_BASE_H

#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor called" << std::endl;
        this->setup();
    }

    
    virtual ~Base() {
        this->cleanup();
        std::cout << "Base destructor called" << std::endl;
    }

    virtual void setup() {
        std::cout << "Base setup called" << std::endl;
        m_value = 20;
    }

    virtual void cleanup() {
        std::cout << "Base cleanup called" << std::endl;
    }
    int get_value() {
        return m_value;
    }

protected:
    int m_value {};
};

#endif