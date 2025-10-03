#ifndef _FREDRIC_PERSON_H
#define _FREDRIC_PERSON_H

#include <iostream>
#include <string>
#include <string_view>

class Person {
    friend std::ostream& operator<<(std::ostream& os, const Person& person);

public:
    Person() = default;
    Person(std::string_view fname, std::string_view lname);
    ~Person() = default;

    std::string get_fname() const {
        return m_fname;
    }

    std::string get_lname() const {
        return m_lname;
    }

    void set_fname(std::string_view fname) {
        m_fname = fname;
    }
    void set_lname(std::string_view lname) {
        m_lname = lname;
    }

private:
    std::string m_fname{};
    std::string m_lname{};
};

#endif