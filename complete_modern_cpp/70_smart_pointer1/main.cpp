#include "integer.h"
#include <iostream>

void display(Integer* p) {
    if(!p) return;
    std::cout << p->get_value() << std::endl;
}

Integer* get_pointer(int value) {
    Integer* p = new Integer(value);
    return p;
}

void operate(int value) {
    Integer* p = get_pointer(value);
    if(!p) {
        p = new Integer{value};
    }
    p->set_value(100);
    display(p);
    delete p;
    p = nullptr;
    p = new Integer();
    *p = __LINE__;
    display(p);
    delete p;
    p = nullptr;
}



int main(int argc, char* argv[]) {
    operate(5);
    return EXIT_SUCCESS;
}