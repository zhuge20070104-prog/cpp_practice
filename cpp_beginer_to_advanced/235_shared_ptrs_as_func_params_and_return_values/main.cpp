#include <iostream>
#include <memory>
#include "dog.h"

void pass_by_value(std::shared_ptr<Dog> dog) {
    std::cout << "Inside function by value: " << dog->get_name() << '\n';
    std::cout << "Count in function: " << dog->use_count() << '\n';
}

void pass_by_non_const_ref(std::shared_ptr<Dog>& dog) {
    dog->set_name("main_dog_changed");
    std::cout << "Inside function non const ref: " << dog->get_name() << '\n';
    std::cout << "Count in function: " << dog->use_count() << '\n';
}

void pass_by_const_ref(const std::shared_ptr<Dog>& dog) {
    // Ptr is const, can't be changed or set to null
    // dog.reset();
    dog->set_name("main_dog_changed");
    std::cout << "Inside function const ref: " << dog->get_name() << '\n';
    std::cout << "Count in function: " << dog.use_count() << '\n';
}


std::shared_ptr<Dog> return_by_value(std::shared_ptr<Dog>& dog) {
    dog->set_name("dog_returned");
    std::cout << "Inside func return by value: " << dog->get_name() << '\n';
    std::cout << "Count in function: " << dog.use_count() << '\n';
    return dog;
}


std::shared_ptr<Dog>& return_by_ref(std::shared_ptr<Dog>& dog) {
    dog->set_name("dog_returned_by_ref");
    std::cout << "Inside function return by ref: " << dog->get_name() << '\n';
    std::cout << "Count in function: " << dog.use_count() << '\n';
    return dog;
}


int main(int argc, char* argv[]) {
    std::shared_ptr<Dog> dog{std::make_shared<Dog>("main_dog")};

    std::cout << "count in main: " << dog.use_count() << '\n';
    pass_by_value(dog);

    std::cout << "Count in main: " << dog.use_count() << '\n';

    pass_by_non_const_ref(dog);
    std::cout << "Count in main: " << dog.use_count() << '\n';

    pass_by_const_ref(dog);
    std::cout << "Count in main: " << dog.use_count() << '\n';
    
    return_by_value(dog);
    std::cout << "count in main : " << dog.use_count() << '\n';

    return_by_ref(dog);
    std::cout << "count in main : " << dog.use_count() << '\n';
    return EXIT_SUCCESS;
}

