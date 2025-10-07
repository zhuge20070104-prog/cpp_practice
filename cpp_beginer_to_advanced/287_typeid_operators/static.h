#ifndef _FREDRIC_STATIC_H
#define _FREDRIC_STATIC_H

#include <iostream>

class StaticBase {
public:
    void do_something() {
        std::cout << "StaticBase::do_something() called" << std::endl;
    }
    ~StaticBase() = default;
};

class StaticDerived: public StaticBase {
public:
    void do_something() {
        std::cout << "StaticDerived::do_something() called" << std::endl;
    }
    ~StaticDerived() = default;
};

#endif