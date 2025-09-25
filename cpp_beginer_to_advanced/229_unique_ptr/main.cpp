#include <iostream>
#include <memory>
#include "dog.h"

int main(int argc, char* argv[]) {
    Dog* dog2 {new Dog{"Gloa"}};

    std::unique_ptr<Dog> up_dog1 {dog2};

    up_dog1->print_dog();
    // explicitly initializing the Dog using new
    std::unique_ptr<Dog> up_dog2 {new Dog{"Bola"}};
    up_dog2->print_dog();

    up_dog2->set_name("Pola");
    up_dog2->print_dog();

    // raw pointer managed by the up_dog2 unique_ptr
    // get returns raw pointer, * derefrences that pointer
    // which gives the object, . operator used to access get_name
    std::cout << (*(up_dog2.get())).get_name() << '\n';

    std::unique_ptr<Dog> up_dog3 {std::make_unique<Dog>("Zulu")};

    up_dog3->print_dog();

    up_dog3->set_name("Yulu");
    up_dog3->print_dog();

    std::cout << (*(up_dog3.get())).get_name() << '\n';


    std::unique_ptr<Dog> a_dog = std::make_unique<Dog>("test");
    // Moving is allowed
    std::unique_ptr<Dog> move_the_dog {std::move(a_dog)};
    move_the_dog->set_name("Dog is moved");
    move_the_dog->print_dog();

    // Moved dog is nullptr now
    std::cout << a_dog << '\n';

    // We can also reset the unique_ptr
    move_the_dog.reset();
    std::cout << move_the_dog << '\n';

    return EXIT_SUCCESS;
}

