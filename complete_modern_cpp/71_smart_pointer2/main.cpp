#include "integer.h"
#include <iostream>
#include <memory>


void display(Integer* p) {
    if(!p) return;
    std::cout << p->get_value() << std::endl;
}

Integer* get_pointer(int value) {
    Integer* p = new Integer(value);
    return p;
}

void store(std::unique_ptr<Integer> p) {
    std::cout << "Storing data into a file: " << p->get_value() << std::endl;
}

void store_by_ref(std::unique_ptr<Integer>& p) {
    std::cout << "Storing data using ref: " << p->get_value() << std::endl;
}

void operate(int value) {
    std::unique_ptr<Integer> p {get_pointer(value)};
    
    if(!p) {
        p.reset(new Integer{value});
    }
    p->set_value(100);
    display(p.get());
    
    p.reset(new Integer{});
    *p = __LINE__;
    display(p.get());
    store(std::move(p));
    // move完就不能用了
}

void operate2(int value) {
    std::unique_ptr<Integer> p {get_pointer(value)};
    
    if(!p) {
        p.reset(new Integer{value});
    }
    p->set_value(100);
    display(p.get());
    
    p.reset(new Integer{});
    *p = __LINE__;
    display(p.get());
    
    store_by_ref(p);
    *p = 200;
    std::cout << "After store by reference, we can still make use of p: " << p->get_value() << std::endl; 
}

int main(int argc, char* argv[]) {
    operate(5);
    operate2(10);
    return EXIT_SUCCESS;
}