#include "engineer.h"

std::ostream& operator<<(std::ostream& os, const Engineer& engineer) {
    os << engineer.get_fullname() << ", " << engineer.get_age();
    os << ", " << engineer.get_address() << ", " << engineer.m_contact_count;
    return os;
}

Engineer::Engineer(std::string_view fullname, int age, std::string_view address, int contact_count):
    Person{fullname, age, address}, m_contact_count{contact_count} {
    std::cout << "Engineer received the data\n";
}