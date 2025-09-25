#include "dog.h"


Dog::Dog(const std::string& name) : m_name(name) {
}

Dog::~Dog() {
    std::cout << "Dog destructor called for: " << m_name << '\n';
}