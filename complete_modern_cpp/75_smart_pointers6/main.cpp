#include <iostream>
#include <memory>
// Forward declaration
class Employee;

class Project {
public:
    std::shared_ptr<Employee> m_emp;
    Project() {
        std::cout << "Project()" << std::endl;
    }
    ~Project() {
        std::cout << "~Project()" << std::endl;
    }
 };

 class Employee {
public:
    std::weak_ptr<Project> m_proj;   
    // std::shared_ptr<Project> m_proj;  不能用std::shared_ptr，循环引用会导致引用计数变为2，两边都是2，减完还有1，释放不了，导致内存泄露
    Employee() {
        std::cout << "Employee()" << std::endl;
    }

    ~Employee() {
        std::cout << "~Employee()" << std::endl;
    }

 };


int main(int argc, char* argv[]) {

    std::shared_ptr<Employee> emp {new Employee};
    std::shared_ptr<Project> proj {new Project};

    emp->m_proj = proj;
    proj->m_emp = emp;

    return EXIT_SUCCESS;
}