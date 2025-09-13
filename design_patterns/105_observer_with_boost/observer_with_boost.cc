#include "observer_with_boost.h"

Person::Person(int age_): age(age_) {
        Observer observer;
        property_changed.connect(observer);
}

int Person::get_age() const {
        return age;
}

void Person::set_age(int age_) {
    if(this->age == age_) return;
    this->age = age_;
    property_changed(*this, "age");
}

void Observer::operator()(Person& p, std::string const& prop_name) const {
    std::cout << prop_name << " has been changed";
    if(prop_name == "age") {
        std::cout << " to " << p.get_age();
    }
    std::cout << "\n";
}
