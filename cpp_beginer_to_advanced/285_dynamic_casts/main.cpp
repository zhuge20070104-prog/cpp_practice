#include <iostream>
#include <memory>
#include "dog.h"
#include "feline.h"
#include "animal.h"


Feline* animal_to_feline(Animal* animal_ptr) {
    return dynamic_cast<Feline*>(animal_ptr);
}

Feline& animal_to_feline_ref(Animal& animal_ref) {
    return dynamic_cast<Feline&>(animal_ref);
}

int main(int argc, char* argv[]) {
   
    Animal* p_animal {new Feline};

    Feline* p_feline {dynamic_cast<Feline*>(p_animal)};

    p_feline->do_feline_thing();


    Dog* p_dog {dynamic_cast<Dog*>(p_animal)};

    if(p_dog) {
        p_dog->dog_speed();
    } else {
        std::cout << "Animal to dog cast has failed\n";
    }

    Feline feline1;
    Animal& animal_ref {feline1};

    Feline& feline_ref {dynamic_cast<Feline&>(animal_ref)};

    feline_ref.do_feline_thing();


    Feline* p_feline2 {dynamic_cast<Feline*>(&animal_ref)};

    if(p_feline2) {
        p_feline2->do_feline_thing();
    } else {
        std::cout << "Can't cast base ref to derived ptr\n";
    }

    Animal* p_animal2 {new Feline};

    animal_to_feline(p_animal2)->do_feline_thing();

    animal_to_feline_ref(animal_ref).do_feline_thing();

    return EXIT_SUCCESS;
}