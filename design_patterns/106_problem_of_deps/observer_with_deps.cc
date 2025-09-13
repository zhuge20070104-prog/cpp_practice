#include "observer_with_deps.h"

Person::Person(int age_): age(age_) {
        Observer observer;
        property_changed.connect(observer);
}

int Person::get_age() const {
        return age;
}

void Person::set_age(int age_) {
    if(this->age == age_) return;
    auto old_can_vote = get_can_vote();
    this->age = age_;
    property_changed(*this, "age");

    if(old_can_vote != get_can_vote()) {
        property_changed(*this, "can_vote");
    }
}

bool Person::get_can_vote() const {
    return age >= 16;
}

void Observer::operator()(Person& p, std::string const& prop_name) const {
    std::cout << prop_name << " has been changed";
    if(prop_name == "age") {
        std::cout << " to " << p.get_age();
    } 
    if(prop_name == "can_vote") {
        std::string can_vote_str = ((p.get_can_vote() == true) ? " can vote": " can not vote");
        std::cout << " to " << can_vote_str;
    }
    std::cout << "\n";
}
