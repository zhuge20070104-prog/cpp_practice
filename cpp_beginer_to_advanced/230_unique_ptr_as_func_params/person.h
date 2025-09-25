#ifndef _FREDRIC_PERSON_H_
#define _FREDRIC_PERSON_H_


#include <string>
#include <memory>

class Dog;
class Person {
public:
    Person(const std::string& name);

    ~Person() = default;

    void adopt_dog(std::unique_ptr<Dog> dog);

private:
    int m_age;
    std::string m_name;
};
#endif