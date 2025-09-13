#include <iostream>
#include <memory>

class Project {
public:
    ~Project() {
        std::cout << "~Project()" << std::endl;
    }
};

class Employee {
    std::shared_ptr<Project> m_project;
public:
    void set_project(std::shared_ptr<Project> p) {
        m_project = p;
        std::cout << "ref count: " << m_project.use_count() << std::endl;
    }

    std::shared_ptr<Project> get_project() const {
        return m_project;
    }

    ~Employee() {
        std::cout << "~Employee()" << std::endl;
    }
};

std::shared_ptr<Employee> assign_project() {
    std::shared_ptr<Project> p{new Project{}};
    Employee *e1 = new Employee();
    e1->set_project(p);
    return std::shared_ptr<Employee>(e1);
}

std::shared_ptr<Employee> assign_project1() {
    std::shared_ptr<Employee> emp{new Employee{}};
    std::shared_ptr<Project> p{new Project{}};
    emp->set_project(p);
    return emp;
}


int main(int argc, char* argv[]) {
    // auto sp =  assign_project();
    auto sp1 = assign_project1();

    return EXIT_SUCCESS;
}