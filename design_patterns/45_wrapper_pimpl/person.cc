#include "person.h"
#include "log.h"

class Person::PersonImpl {
    public:
        void greet(Person* p);
};

void Person::PersonImpl::greet(Person* p) {
    B_LOG(info) << "Hello, my name is: " << p->name << "\n";
}

Person::Person(std::string const& name_): name(name_), impl(){}

void Person::greet() {
    impl->greet(this);
}

Person::~Person() {
}