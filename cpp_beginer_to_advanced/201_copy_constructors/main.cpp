#include <iostream>
#include <string>

class Person {
    std::string m_fname {};
    std::string m_lname {};
    int* m_p_age {};


public:
    Person() = default;
    Person(const std::string& fname, const std::string& lname, int age);
    Person(const std::string& fname, const std::string& lname);
    Person(const std::string& lname);
    ~Person();

    Person(const Person& other);

    void set_fname(const std::string& fname) {
        m_fname = fname;
    }

    void set_lname(const std::string& lname) {
        m_lname = lname;
    }

    void set_age(int age) {
        *(this->m_p_age) = age;
    }


    const std::string& get_fname() const {
        return m_fname;
    }

    const std::string& get_lname() const {
        return m_lname;
    }

    const int get_age() const {
        return *(this->m_p_age);
    }

    void print_person() {
        std::cout << "Object addr: " << this << '\n';
        std::cout << "fname: " << m_fname << '\n';
        std::cout << "lname: " << m_lname << '\n';
        std::cout << "age: " << *(this->m_p_age) << '\n';
        std::cout << "age addr: " << this->m_p_age << '\n' << '\n';
    }
};

Person::Person(const std::string& fname, const std::string& lname, int age):
 m_fname{fname}, m_lname{lname}, m_p_age{new int(age)} {
    std::cout << "Main constructor called\n";
}

Person::Person(const std::string& fname, const std::string& lname):
 Person{fname, lname, 0} {

}

Person::Person(const std::string& lname):
 Person{"", lname} {

}


Person::~Person() {
    delete m_p_age;
}

Person::Person(const Person& other): Person{other
    .get_fname(), other.get_lname(), other.get_age()} {

}

int main(int argc, char* argv[]) {
   
    Person p1 {"Tyrell", "Wellick", 29};
    p1.print_person();

    Person p2 {p1};
    p2.set_age(30);

    p2.print_person();
    return EXIT_SUCCESS;
}

