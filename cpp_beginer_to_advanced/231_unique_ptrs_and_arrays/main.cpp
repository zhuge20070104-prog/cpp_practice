#include <iostream>
#include <memory>
#include "dog.h"


int main(int argc, char* argv[]) {
   
    // a stack array
    Dog d_array1[] {Dog{"Dan"}, Dog{"Ham"}, Dog{"Rich"}};
    for(std::size_t i{0}; i<std::size(d_array1); ++i) {
        std::cout << "Static: ";
        d_array1[i].print_dog();
    }


    // allocating on heap
    Dog* p_dog {new Dog[]{Dog{"Jan"}, Dog{"Pam"}, Dog{"Lich"}}};
    for(std::size_t i{0}; i<3; ++i) {
        std::cout << "Dynamic: ";
        p_dog[i].print_dog();
    }

    // necessary
    delete [] p_dog;
    p_dog = nullptr;


    // using the smart pointers - better than the above method
    auto up_dog {std::unique_ptr<Dog[]>{new Dog[]{Dog{"Tan"}, Dog{"Sam"}, Dog{"Dich"}}}};
    for(std::size_t i{0}; i<3; ++i) {
        std::cout << "Unique_ptr: ";
        up_dog[i].print_dog();
    }

    // allocating using make_unique - individual element cant be initialized using this method
    auto uptr_make_uniq_dog {std::make_unique<Dog[]>(3)};
    for(std::size_t i{0}; i<3; ++i) {
        std::cout << "Make_unique ptr: ";
        uptr_make_uniq_dog[i].print_dog();
    }

    return EXIT_SUCCESS;
}

