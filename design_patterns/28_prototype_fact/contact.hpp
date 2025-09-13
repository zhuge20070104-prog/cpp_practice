#ifndef _FREDRIC_CONTACT_HPP_
#define _FREDRIC_CONTACT_HPP_

#include <iostream>
#include <string>
#include <memory>

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
    std::unique_ptr<Address> address;

    // 构造的时候可以直接移动，Address被直接包含到了contact里面，移动后的Address只能和Contact绑定了
    Contact(std::string const& name_, std::unique_ptr<Address> address_): name(name_), address(std::move(address_)) {}

    // 拷贝的时候必须重新构建一个unique_ptr对象，不能移动，因为另外一个contact还需要使用的，注意着点
    Contact(Contact const& other): name(other.name), address(std::make_unique<Address>(*other.address)) {}

    friend std::ostream& operator<<(std::ostream& os, Contact const& contact) {
        return os << "name: [" << contact.name << "] address: " << *contact.address;
    }
};


struct EmployeeFactory {
    static Contact main_contact;
    static Contact aux_contact;
    
    static std::unique_ptr<Contact> new_main_office_employee(std::string const& name, int suite) {
        return new_employee(name, suite, main_contact);
    }

    static std::unique_ptr<Contact> new_aux_office_employee(std::string const& name, int suite) {
        return new_employee(name, suite, aux_contact);
    }
private:
    static std::unique_ptr<Contact> new_employee(std::string const& name, int suite, Contact& proto) {
        auto result = std::make_unique<Contact>(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

Contact EmployeeFactory::main_contact {"", std::make_unique<Address>("123 East Dr", "London", 0)};
Contact EmployeeFactory::aux_contact {"", std::make_unique<Address>("124 West Dr", "Aux", 0)};


#endif