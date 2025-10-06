#include "base.h"

class Derived: public Base {
public:
    Derived() = default;
    virtual ~Derived() = default;

    virtual int add(int x=10, int y=10) const override {
        std::cout << "Derived::add() called" << std::endl;
        return x + y;
    }
};