#include <iostream>
#include <list>

class CMP {
public:
    // 倒序排列
    bool operator()(int const& a, int const& b) {
        return a>b;
    }
};

void print(std::string const& str, std::list<int> const& l) {
    std::cout << str << std::endl;
    using IT = std::list<int>::const_iterator;
    for(IT it = l.begin(); it!=l.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl << "-------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    std::list<int> ls;
    for(int i=0; i<5; ++i) {
        ls.push_front(10+i);
    }

    for(int i=0; i<5; ++i) {
        ls.push_back(10-i);
    }

    print("添加节点后: ", ls);
    ls.unique();
    print("唯一化后: ", ls);

    CMP cmp;
    ls.sort(cmp);
    print("排序后:", ls);


    std::list<int> lst;
    lst.push_back(1000);
    lst.push_back(2000);
    lst.push_back(3000);
    lst.push_back(4000);

    ls.splice(ls.begin(), lst, ++lst.begin(), --lst.end());
    print("ls: ", ls);
    print("lst: ", lst);  // 1000, 4000
    return EXIT_SUCCESS;
}