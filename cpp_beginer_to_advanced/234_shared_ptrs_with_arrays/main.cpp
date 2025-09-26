#include <iostream>
#include <memory>
#include "dog.h"


int main(int argc, char* argv[]) {
   
    std::shared_ptr<int[]> shared_int_array {new int[]{1, 2, 3, 4, 5}};
    std::shared_ptr<Dog[]> shared_dog_array {new Dog[]{Dog{"Dan"}, Dog{"Jude"}}};
    
    for(std::size_t i=0; i<5; ++i) {
        std::cout << shared_int_array[i] << ' ';
    }

    std::cout << '\n';

    for(std::size_t i=0; i<2; ++i) {
        std::cout << shared_dog_array[i].get_name() << ' ';
    }

    std::cout << '\n';
    return EXIT_SUCCESS;
}

