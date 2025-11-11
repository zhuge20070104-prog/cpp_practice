#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

class Employee {
public:
    Employee(std::string first, std::string last, int salary):
        m_first_name(first), m_last_name(last), m_salary(salary) {

    }

    int get_salary() const {
        return m_salary;
    }

    std::string get_sorting_name() const {
        return m_last_name + ", " + m_first_name;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Employee& employee) {
        os << employee.get_sorting_name() << " salary: " << employee.get_salary();
        return os;
    }
private:
    std::string m_first_name;
    std::string m_last_name;
    int m_salary;
};


void print_employees(const std::vector<Employee>& staff) {
    std::for_each(std::begin(staff), std::end(staff), [](const Employee& e) {
        std::cout << e << std::endl;
    });
    std::cout << std::endl;
}


TEST_CASE("Stable sort") {
    std::vector<Employee> staff {
        {"Kate", "Gregory", 1000},
        {"Obvious", "Artificial", 2000},
        {"Fake", "Name", 1000},
        {"Alan", "Turing", 2000},
        {"Grace", "Hopper", 2000},
        {"Anita", "Borg", 2000}
    };

    std::sort(std::begin(staff), std::end(staff), 
        [](Employee e1, Employee e2) {
            return e1.get_salary() < e2.get_salary();
        });
    
    std::cout << "After sorting by salary: " << std::endl;
    print_employees(staff);

    std::sort(std::begin(staff), std::end(staff), 
        [](Employee e1, Employee e2) {
            return e1.get_sorting_name() < e2.get_sorting_name();
        });

    std::cout << "After sorting by sorting name: " << std::endl;
    print_employees(staff);

    std::stable_sort(std::begin(staff), std::end(staff), 
        [](Employee e1, Employee e2) {
            return e1.get_salary() < e2.get_salary();
        });

    std::cout << "After stable sorting by salary: " << std::endl;
    print_employees(staff);
    
}