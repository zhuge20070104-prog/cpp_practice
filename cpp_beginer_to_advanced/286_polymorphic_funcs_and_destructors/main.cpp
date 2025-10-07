#include <iostream>
#include <memory>
#include "base.h"
#include "derived.h"


int main(int argc, char* argv[]) {
   
    Base* p_base {new Derived};
    // the derived part is not created when base part is being built,
    // static binding will cause the base setup() to be called
    std::cout << "p_base->get_value(): " << p_base->get_value() << std::endl;
    delete p_base;
    return EXIT_SUCCESS;
}