#include <iostream>
#include "person.h"
#include "dog.h"


Person::Person(const std::string& name): m_name{name} {}


void Person::adopt_dog(std::unique_ptr<Dog> dog) {
    std::cout << "Person " << m_name << " adopts dog " << dog->get_name() << std::endl;
}