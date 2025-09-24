#include <iostream>


inline int age {2};

inline void print_age() {
    std::cout << "inline age2: " << &age << '\n';
}


void print_age_inline2() {
    print_age();
}


namespace {
    int data {3};

    void print_data() {
        std::cout << "namespace data2: " << &data << '\n';
    }
}


static int static1 {20};


void print_namespace2() {
    print_data();
    std::cout << "static1: " << &static1 << '\n';
}