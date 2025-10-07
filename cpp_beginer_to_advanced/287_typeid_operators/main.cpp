#include <iostream>
#include <memory>
#include "static.h"
#include "dynamic.h"

/**
typeid operator outputs: 
typeid(x).name(): i
typeid(2.2).name(): d
x is an int
typeid(ref_dynamic).name(): 14DynamicDerived
typeid(dynamic).name(): 14DynamicDerived
typeid(ptr_dynamic).name(): P11DynamicBase
typeid(*ptr_dynamic).name(): 14DynamicDerived
typeid(static_derived).name(): 13StaticDerived
typeid(ptr_static).name(): P10StaticBase
typeid(ref_static).name(): 10StaticBase
*/
int main(int argc, char* argv[]) {
    // typeid with fundamental types
    int x {};
    std::cout << "typeid(x).name(): " << typeid(x).name() << std::endl;
    std::cout << "typeid(2.2).name(): " << typeid(2.2).name() << std::endl;

    if(typeid(int) == typeid(x)) {
        std::cout << "x is an int" << std::endl;
    } else {
        std::cout << "x is not an int" << std::endl;
    }

    // typeid with polymorphic types

    DynamicDerived dynamic;
    DynamicBase& ref_dynamic {dynamic};
    
    // queries the type of object ref_dynamic is referencing - dynamic binding
    // ref is of type Base but object is derived
    std::cout << "typeid(ref_dynamic).name(): " << typeid(ref_dynamic).name() << std::endl;
    // static binding
    std::cout << "typeid(dynamic).name(): " << typeid(dynamic).name() << std::endl;

    DynamicBase* ptr_dynamic {&dynamic};

    std::cout << "typeid(ptr_dynamic).name(): " << typeid(ptr_dynamic).name() << std::endl;
    std::cout << "typeid(*ptr_dynamic).name(): " << typeid(*ptr_dynamic).name() << std::endl;

    // typeid with non-polymorphic types
    StaticDerived static_derived;
    StaticBase* ptr_static {&static_derived};
    StaticBase& ref_static {static_derived};
    std::cout << "typeid(static_derived).name(): " << typeid(static_derived).name() << std::endl;
    std::cout << "typeid(ptr_static).name(): " << typeid(ptr_static).name() << std::endl;
    std::cout << "typeid(ref_static).name(): " << typeid(ref_static).name() << std::endl;
    
    return EXIT_SUCCESS;
}