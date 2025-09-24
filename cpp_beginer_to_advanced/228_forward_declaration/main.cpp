#include <iostream>
#include "farm.h"
#include "dog.h"

int main(int argc, char* argv[]) {
   
    Farm farm;
    Dog dog {5};
    farm.include_dog(dog);

    return EXIT_SUCCESS;
}

