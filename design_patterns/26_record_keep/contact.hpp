#ifndef _FREDRIC_CONTACT_HPP_
#define _FREDRIC_CONTACT_HPP_

#include <iostream>
#include <string>

struct Address {
    std::string street;
    std::string city;
    int suite;

    Address(std::string const& street_, std::string const& city_, int suite_): street(street_), city(city_), suite(suite_) {
    }

    friend std::ostream& operator<<(std::ostream& os, Address const& address) {
        return os << " [street: " << address.street << " city: " << address.city << " suite: " << address.suite << "]";  
    }
};

struct Contact {
    std::string name;
    Address address;

    Contact(std::string const& name_, Address const& address_): name(name_), address(address_) {}

    friend std::ostream& operator<<(std::ostream& os, Contact const& contact) {
        return os << "name: [" << contact.name << "] address: " << contact.address;
    }
};



#endif