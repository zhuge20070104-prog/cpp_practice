#ifndef _FREDRIC_OBSERVER_WITH_DEPS_H_
#define _FREDRIC_OBSERVER_WITH_DEPS_H_
#include <vector>
#include <string>
#include <iostream>
#include "observerable_safety.hpp"

template <typename T>
struct Observer {
    virtual void field_change(
        T& source,
        std::string const& field_name
    ) = 0;
};

class Person: public Observerable<Person> {
    int age;

public:
    Person(int age_): age(age_) {}

    int get_age() const {
        return age;
    }

    void set_age(int age_) {
        if(this->age == age_) return;
        this->age = age_;
        notify(*this, "age");
    }
};

struct ConsolePersonObserver: public Observer<Person> {
    void field_change(Person& person, std::string const& field_name) {
        std::cout << "Person's " << field_name << " has changed to ";
        if(field_name == "age") {
            std::cout << person.get_age();
        }
        std::cout << "\n";
    }
};

struct TrafficAdministration: public Observer<Person> {
    void field_change(Person& person, std::string const& field_name) {
        if(field_name == "age") {
            if(person.get_age() < 17) {
                std::cout << "Whoa there, you're not old enough to drive!\n";
            } else {
                std::cout << "Oh, ok, we no longer care!\n";
                person.unsubscribe(*this);
            }
        }
    }
};

#endif