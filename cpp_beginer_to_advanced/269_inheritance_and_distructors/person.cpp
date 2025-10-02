#include "person.h"

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.m_fullname << " " << person.m_age << "," << person.m_address;
    return os;
}

Person::Person(std::string_view fullname, int age, std::string_view address):
     m_fullname{fullname}, m_age{age}, m_address{address} {
    std::cout << "Person received the data\n";
}