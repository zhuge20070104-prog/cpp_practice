#ifndef _FREDRIC_OPEATOR_NEW_DEL_H_
#define _FREDRIC_OPEATOR_NEW_DEL_H_

#include "new_del.h"

#include <cstddef>
#include <memory>
#include <iostream>


bool new_instrumentation_on = false;
new_instrument::new_instrument() {
    new_instrumentation_on = true;
}

new_instrument::~new_instrument() {
    new_instrumentation_on = false;
}

void instrument_new(bool f) {
    new_instrumentation_on = f;
}


void* operator new(std::size_t size) noexcept(false) {
    void* p = malloc(size);
    if(new_instrumentation_on) {
        std::cout << "::operator new (" << size << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    }
    return p;
}

void* operator new[](std::size_t size) noexcept(false)  {
    void* p = malloc(size);
    if(new_instrumentation_on) {
        std::cout << "::operator new[] (" << size << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    }
    return p;
}

void operator delete(void* p) noexcept(true) {
    if(new_instrumentation_on) {
        std::cout << "operator delete 0x" << std::hex << p << std::dec << std::endl;
    }
    free(p);
}

void operator delete[](void* p) noexcept(true) {
    if(new_instrumentation_on) {
        std::cout << "operator delete [] 0x" << std::hex << p << std::dec << std::endl;
    }
    free(p);
}

#endif