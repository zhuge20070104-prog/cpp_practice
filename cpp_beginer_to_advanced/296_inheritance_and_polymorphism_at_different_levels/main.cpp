#include <iostream>
#include <memory>
#include "animal.h"
#include "feline.h"
#include "dog.h"
#include "cat.h"
#include "bird.h"
#include "pigeon.h"
#include "crow.h"


int main(int argc, char* argv[]) {
    Dog dog1 {"Brown", "Dog1"};
    Cat cat1 {"White", "Cat1"};
    Pigeon pigeon1 {"Gray", "Pigeon1"};
    Crow crow1 {"Black", "Crow1"};

    Animal* animal_ptr[] {&dog1, &cat1, &pigeon1, &crow1};
    for(auto& animal: animal_ptr) {
        animal->breathe();
    }

    Dog dog2 {"White", "Dog2"};
    Cat cat2 {"Yellow", "Cat2"};
    Pigeon pigeon2 {"Blue", "Pigeon2"};
    Feline* feline_ptr[] {&dog2, &cat2};

    for(auto& feline: feline_ptr) {
        feline->run();
    }

   
    Bird* bird_ptr[] {&crow1, &pigeon2};
    for(auto& bird: bird_ptr) {
        bird->fly();
    }
    
    return EXIT_SUCCESS;
}