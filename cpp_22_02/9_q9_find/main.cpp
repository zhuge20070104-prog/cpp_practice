#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <list>
#include <iomanip>


class A {
    int a;
public:
    A(int a): a(a) {}

    int getA() const {
        return a;
    }

    void setA(int a) {
        this->a = a;
    }

    /*Insert code here*/
    // 重载 != 符号不行，必须重载 ==符号
    bool operator!= (A const& b) const {
        return this->a != b.a;
    }

    bool operator == (A const& b) const {
        return (this->a == b.a);
    }
};


struct add10 {
    void operator()(A& a)  {
        a.setA(a.getA() + 10);
    }
};

int main(int argc, char* argv[]) {
   
    int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};

    std::vector<A> v1(t, t+10);

    std::for_each(v1.begin(), v1.end(), add10());

    // Expect output: compilation error, 没有等于操作符
    std::vector<A>::iterator it = find(v1.begin(), v1.end(), A(7));

    std::cout << it->getA() << std::endl;
    return EXIT_SUCCESS;
} 

