#include "person.h"
#include <iostream>

Person::Person(const std::string& name): m_name{name} {}

Person::~Person() {
    std::cout << "Person destructor called for " << m_name << '\n';
}