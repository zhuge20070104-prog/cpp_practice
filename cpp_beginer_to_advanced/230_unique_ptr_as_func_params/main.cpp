#include <iostream>
#include <memory>
#include "dog.h"
#include "person.h"

void pass_dog_by_value(std::unique_ptr<Dog> dog) {
    dog->print_dog();
}

void pass_dog_by_ref(const std::unique_ptr<Dog>& dog) {
    dog->print_dog();
    dog->set_name("Ghoul");
    dog->print_dog();
}

std::unique_ptr<Dog> return_dog_by_value() {
    std::unique_ptr<Dog> dog_local {std::make_unique<Dog>("Local Dog")};
    std::cout << "Inside the func: " << dog_local.get() << std::endl;
    return dog_local;
}

int main(int argc, char* argv[]) {
    std::unique_ptr<Dog> dog1 {std::make_unique<Dog>("Daniel")};

    pass_dog_by_value(std::move(dog1));

    // unique ptr is destroyed in function call, dog1 is set to null when moved to local
    // unique ptr which is in the function
    std::cout << "After the func: " << dog1.get() << std::endl;

    std::unique_ptr<Dog> dog2 {std::make_unique<Dog>("Sean")};

    Person person1 {"Leon"};

    person1.adopt_dog(std::move(dog2));

    // source Dog is null now
    std::cout << "After the func: " << dog2.get() << std::endl;

    // anonymous objects are moved implicitly
    // copy is not allowed, move is allowed - no copies are made in the below function call
    pass_dog_by_value(std::make_unique<Dog>("Temp Dog"));

    // dog is destroyed after the function call
    // taking the unique ptr by ref. works, copying doesn't work
    pass_dog_by_ref(std::make_unique<Dog>("Ref Dog"));

    std::cout << "In main()\n";

    // no copy is returned
    auto ptr = return_dog_by_value();

    std::cout << "Inside main(): " << ptr.get() << std::endl;
    ptr->print_dog();

    return EXIT_SUCCESS;
}

