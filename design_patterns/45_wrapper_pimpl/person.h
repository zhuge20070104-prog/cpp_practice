#ifndef _FREDRIC_PERSON_H_
#define _FREDRIC_PERSON_H_

#include "pimpl.hpp"
#include <string>

class Person {
    class PersonImpl;
    PImpl<PersonImpl> impl;  


public:
    std::string name;
    Person(std::string const& name_);
    ~Person();

    void greet();
};
#endif