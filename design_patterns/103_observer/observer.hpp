#ifndef _FREDIRC_OBSERVER_HPP_
#define _FREDIRC_OBSERVER_HPP_

#include "oberserverable.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct Observer {
    virtual void field_change(T& source, std::string const& field_name) = 0;
};

// 被观察者
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


// 观察者
struct ConsolePersonObserver: public Observer<Person> {
    void field_change(Person& source, std::string const& field_name) override {
        std::cout << "Person's " << field_name << " has changed to ";
        if(field_name == "age") {
            std::cout << source.get_age();
        }
        std::cout << "\n";
    }
};
#endif