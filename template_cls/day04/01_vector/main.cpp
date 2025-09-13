#include <vector>
#include <iostream>
#include <cstdio>
#include <string>

class Student {
public:
    Student(std::string const& name=""): m_name(name) {
        std::cout << "缺省构造了: " << m_name << " (" << this << ")" << std::endl;
    }

    Student(Student const& that): m_name(that.m_name) {
        std::cout << "用: " << that.m_name << " (" << &that << ")拷贝构造了: "
            << m_name << " (" << this << ") " << std::endl;
    }

    ~Student() {
        std::cout << "析构了: " << m_name << " (" << this << ")" << std::endl;
    }

private:
    std::string m_name;
};

int main(int argc, char* argv[]) {
    std::vector<Student> vs;
    vs.reserve(10);

    vs.push_back(Student("张三"));
    vs.push_back(Student("李四"));
    vs.push_back(Student("王五"));

    getchar();
    return EXIT_SUCCESS;
}