#include <iostream>
#include <memory>
#include "dog.h"
#include "person.h"


int main(int argc, char* argv[]) {
    std::shared_ptr<int> shared_int {std::make_shared<int>(9)};
    std::shared_ptr<Dog> shared_dog {std::make_shared<Dog>("Jimmy")};

    std::weak_ptr<int> weak_int {shared_int};
    std::weak_ptr<Dog> weak_dog {shared_dog};

    std::shared_ptr<Dog> weak_to_shared {weak_dog.lock()};
    std::cout << weak_to_shared.use_count() << '\n';
    std::cout << weak_to_shared.get() << '\n';
    std::cout << weak_to_shared->get_name() << '\n';

    std::shared_ptr<Person> shared_person1 {std::make_shared<Person>("Dan")};
    std::shared_ptr<Person> shared_person2 {std::make_shared<Person>("Jude")};

    shared_person1->set_friend(shared_person2);
    shared_person2->set_friend(shared_person1);

    std::cout << "shared_person1.use_count(): " << shared_person1.use_count() << '\n';
    std::cout << "shared_person2.use_count(): " << shared_person2.use_count() << '\n';
    return EXIT_SUCCESS;
}

