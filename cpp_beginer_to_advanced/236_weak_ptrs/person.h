#ifndef _FREDRIC_PERSON_H_
#define _FREDRIC_PERSON_H_

#include <memory>
#include <string>

class Person {
public:
    Person() = default;

    Person(const std::string& name);
    ~Person();

    void set_friend(std::shared_ptr<Person> p) {
        m_friend = p;
    }

private:
    std::weak_ptr<Person> m_friend;
    std::string m_name {"Unnamed"};
};

#endif