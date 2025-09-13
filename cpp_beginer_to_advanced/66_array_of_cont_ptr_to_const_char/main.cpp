#include <iostream>
#include <algorithm>

struct StudentPrinter {
    StudentPrinter(char const* const * students_, std::size_t sz_):
        students(students_),
        sz(sz_) {}

    void operator()() {
        std::for_each(students, students + sz, [](char const* const student) {
            std::cout << student << std::endl;
        });
    }
private:
    char const* const * students;
    std::size_t sz;
};

int main(int argc, char *argv[]) {
    
    char const* const students[] = {
        "Daniel Gray",
        "Tuna Philbe",
        "The Rock",
        "Kumar Singh",
        "Sam Ali",
        "Dave Mahoro"
    };

    // print out the students
    StudentPrinter p(students, std::size(students));
    p();

    // 指针的指向不能变，所以会error
    char const* new_student {"Bob the great"};
    // students[0] = new_student;

    std::cout << std::endl;
    
    // print out the students
    StudentPrinter p1(students, std::size(students));
    p1();

    return EXIT_SUCCESS;
}