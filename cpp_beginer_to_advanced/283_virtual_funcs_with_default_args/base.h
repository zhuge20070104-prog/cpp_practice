#ifndef _FREDRIC_BASE_H
#define _FREDRIC_BASE_H

#include <iostream>


class Base {
public:
    Base() = default;
    virtual ~Base() = default;

    virtual int add(int x=5, int y=5) const {
        std::cout << "Base::add() called" << std::endl;
        return x + y;
    }
};
#endif