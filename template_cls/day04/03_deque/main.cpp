#include <iostream>
#include <algorithm>
#include <deque>

class Student {
public:
    Student(std::string const& name, int age): m_name(name), m_age(age) {}

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

void print(std::string const& str, std::deque<Student> const& d) {
    std::cout << str << std::endl;
    using IT = std::deque<Student>::const_iterator;
    for(IT it=d.begin(); it!=d.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl << "-----------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    std::deque<Student> di;
    di.push_front(Student("张飞", 22));
    di.push_front(Student("赵云", 20));
    di.push_front(Student("马超", 26));
    di.push_back(Student("关羽", 28));
    di.push_back(Student("黄忠", 44));

    print("添加节点后:", di);
    using IT = std::deque<Student>::iterator;
    di.insert(di.begin(), Student("刘备", 50));
    print("在迭代器指向的位置添加节点后:", di);
    di.erase(di.begin());
    print("删除迭代器指向的节点后:", di);

    IT it = di.begin();
    *it = Student("吕布", 36);
    print("更改迭代器指向的节点后:", di);

    IT fit = std::find(di.begin(), di.end(), Student("黄忠", 44));
    if(fit != di.end()) {
        di.erase(fit);
    }
    print("找到黄忠并删除以后:", di);

    sort(di.begin(), di.end());
    print("排序后:", di);
    
    return EXIT_SUCCESS;
}