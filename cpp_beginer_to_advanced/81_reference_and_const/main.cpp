#include <iostream>


int main(int argc, char* argv[]) {
    std::cout << std::endl;
    std::cout << "Non const reference: " << std::endl;
    int age {27};
    int &ref_age {age};
    std::cout << "age: " << age << std::endl;
    std::cout << "ref_age: " << ref_age << std::endl;

    // can modify original variable through reference
    std::cout << std::endl;
    std::cout << "modify original variable through reference: " << std::endl;
    ref_age++; 
    std::cout << "age: " << age << std::endl;
    std::cout << "ref_age: " << ref_age << std::endl;
    

    std::cout << std::endl;
    std::cout << "const reference, can't modify value through reference: " << std::endl;
    int const& cref_age {age};
    // Compile error
    // cref_age++;
    std::cout << "age: " << age << std::endl;
    std::cout << "cref_age: " << cref_age << std::endl;

    // Simulating const reference behavior with pointers
    int const* const p_age{&age};
    // Compile error
    // *p_age = 45;
    std::cout << "age: " << age << std::endl;
    std::cout << "*p_age: " << *p_age << std::endl;

    return EXIT_SUCCESS;
}