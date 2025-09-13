#include <iostream>
#include <vector>
#include <algorithm>

class Student {
public:
    Student(std::string const& name="", int age=0): m_name(name), m_age(age) {}

    bool operator==(Student const& that) const {
        return m_name == that.m_name && m_age == that.m_age;
    }

    bool operator<(Student const& that) const {
        return m_age < that.m_age;
    }

    bool operator>(Student const& that) const {
        return m_age > that.m_age;
    }
private:
    std::string m_name;
    int m_age;

    friend std::ostream& operator<<(std::ostream& os, Student const& that);
};

std::ostream& operator<<(std::ostream& os, Student const& that) {
    return os << that.m_name << ":" << that.m_age;
}


void print(std::string const& str, std::vector<Student> const& v) {
    std::cout << str << std::endl;
    using IT = std::vector<Student>::const_iterator;
    for(IT it=v.begin(); it!=v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl << "---------------------" << std::endl;
}

class CMP {
public:
    bool operator() (Student const& a, Student const& b) {
        return a > b;
    }
};


int main(int argc, char* argv[]) {
    std::vector<Student> vs;
    vs.reserve(10);
    vs.push_back(Student("张飞", 22));
    vs.push_back(Student("赵云", 20));
    vs.push_back(Student("关羽", 25));
    vs.push_back(Student("马超", 27));
    vs.push_back(Student("黄忠", 44));
    print("添加节点后:", vs);

    vs.insert(vs.begin(), Student("刘备", 38));
    print("在迭代器指定的位置添加节点后:", vs);

    vs.erase(vs.begin());
    print("删除迭代器指定的节点以后:", vs);

    using IT = std::vector<Student>::iterator;
    IT it = vs.begin();
    *it = Student("诸葛亮", 18);
    print("更改迭代器指向的节点以后:", vs);

    IT fit = std::find(vs.begin(), vs.end(), Student("赵云", 20));
    if(fit!=vs.end()) {
        vs.erase(fit);
    }
    print("找到赵云并删除后:", vs);

    CMP cmp; // 比较器
    sort(vs.begin(), vs.end(), cmp);
    print("排序后: ", vs);

    return EXIT_SUCCESS;
}