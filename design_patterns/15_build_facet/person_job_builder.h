#ifndef _FREDRIC_PERSON_JOB_BUILDER_H_
#define _FREDRIC_PERSON_JOB_BUILDER_H_

#include "person_builder.h"
#include <string>

class PersonJobBuilder: public PersonBuilderBase {
    using Self = PersonJobBuilder;

public:
    explicit PersonJobBuilder(Person* person): PersonBuilderBase(person) {}

    Self& at(std::string const& company_name) {
        person->company_name = company_name;
        return *this;
    }

    Self& as_a(std::string const& postion) {
        person->position = postion;
        return *this;
    }

    Self& earning(int annual_income) {
        person->annual_income = annual_income;
        return *this;
    }
};

#endif