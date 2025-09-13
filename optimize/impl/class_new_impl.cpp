#include <iostream>
#include <memory>
#include "new_del.h"


class MyAllocator {
public:
    void* operator new(std::size_t n);
    void operator delete(void* p);
    void* operator new[](std::size_t n);
    void operator delete[](void* p);
    void AllocateBuffer();
private:
    std::unique_ptr<short> p_;    
};


 void* MyAllocator::operator new(std::size_t n) {
    void* p = malloc(n);
    if(new_instrumentation_on) {
        std::cout << "MyAllocator::operator new (" << n << ") allocated at 0x" << std::hex << p << std::dec << std::endl;
    }
    return p;
 }

 void MyAllocator::operator delete(void* p) {
    if(new_instrumentation_on) {
        std::cout << "MyAllocator::operator delete 0x" << std::hex << p << std::dec << std::endl;
    }
    free(p);
 }

 void* MyAllocator::operator new[](std::size_t n) {
    void* p = malloc(n);
    if(new_instrumentation_on) {
        std::cout << "MyAllocator::operator new [] allocated at 0x" << std::hex << p << std::dec << std::endl;
    }
    return p;
 }

 void MyAllocator::operator delete[](void* p) {
    if(new_instrumentation_on) {
        std::cout << "MyAllocator::operator delete[] 0x" << std::hex << p << std::dec << std::endl;
    }
    free(p);
 }

 void MyAllocator::AllocateBuffer() {
    p_.reset(new short(12345));
 }


int test_class_new(int test_no, unsigned long multipiler) {
    bool rc = true;

    switch(test_no) {
        case 0: {
            return 1;
        }
        case -1: {
            return -1;
        }
        case 1: {
            new_instrument ni;
            {
                std::unique_ptr<MyAllocator> pmoa(new MyAllocator);
                pmoa->AllocateBuffer();
                std::unique_ptr<MyAllocator[]> pa_moa(new MyAllocator[3]);
                // ::new ((void*)0) MyAllocator;
            }

            struct {int x, y; int z[100]; } c, d;
            c = d;
        }
        break;
    }

    return (rc)? 1: 0;
}