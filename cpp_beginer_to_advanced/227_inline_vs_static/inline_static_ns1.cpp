#include <iostream>


inline int age {2};

inline void print_age() {
    std::cout << "inline age1: " << &age << '\n';
}


void print_age_inline1() {
    print_age();
}


namespace {
    int data {3};

    void print_data() {
        std::cout << "namespace data1: " << &data << '\n';
    }
}


static int static1 {20};


void print_namespace1() {
    print_data();
    std::cout << "static1: " << &static1 << '\n';
}