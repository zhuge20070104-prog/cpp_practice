#include <iostream>
#include <memory>
#include "dog.h"
#include "feline.h"
#include "animal.h"


int main(int argc, char* argv[]) {
    Dog dog1;

    std::unique_ptr<Animal> animal_ptr = std::make_unique<Dog>();
  

    return EXIT_SUCCESS;
}