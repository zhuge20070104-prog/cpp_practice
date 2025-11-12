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


std::vector<int> v {4, 1, 0, 1, -2, 3, 7, -6, 2, 0, 0, -9, 9};

template <typename T>
void print_vector(const std::vector<T>& v) {
    std::for_each(std::begin(v), std::end(v), [](auto const& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}

TEST_CASE("Find the largest element") {
    int high = *std::max_element(std::begin(v), std::end(v));
    int low = *std::min_element(std::begin(v), std::end(v));
    std::cout << "max element: " << high << '\n';
    std::cout << "min element: " << low << '\n';
}


TEST_CASE("lower_bound and upper_bound") {
    std::vector<int> v2(v);
    std::cout << "For sorted vector: " << '\n';
    std::sort(std::begin(v2), std::end(v2));
    int low = *(std::begin(v2));
    int high = *(std::end(v2) - 1);
    std::cout << "max element: " << high << '\n';
    std::cout << "min element: " << low << '\n';

    // upper_bound, sorted集合中第一个大于指定元素的元素
    // 例如集合是1，2，3，4，5，传入 3, 则返回4
    int positive = *std::upper_bound(std::begin(v2), std::end(v2), 0);
    std::cout << "first positive element: " << positive << '\n';


    std::vector<Employee> staff {
        {"Kate", "Gregory", 1000},
        {"Obvious", "Artificial", 2000},
        {"Fake", "Name", 1000},
        {"Alan", "Turing", 2000},
        {"Grace", "Hopper", 2000},
        {"Anita", "Borg", 2000}
    };

    std::sort(std::begin(staff), std::end(staff), [](Employee e1, Employee e2) {
        return e1.get_sorting_name() < e2.get_sorting_name();
    });

    // lower_bound，sorted集合中第一个 不大于指定元素的元素，
    // <=value 的元素
    auto p = std::lower_bound(std::begin(staff), std::end(staff), "Gregory, Kate", 
        [](Employee e1, std::string name){
            return e1.get_sorting_name() < name;
        });
    
    std::cout << "first element not less than Gregory, Kate: " << *p << '\n';
}