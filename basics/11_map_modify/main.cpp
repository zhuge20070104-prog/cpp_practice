#include <string>
#include <iostream>
#include <map>

// std::map装入的对象会产生 copy
struct Obj {
    int a;
    int b;
};
int main(int argc, char* argv[]) {
    std::map<int, Obj>  m_obj;
    Obj o {11, 22};

    m_obj[1] = o;
    m_obj[1].a = 33;
    m_obj[1].b =44;
    std::cout << o.a << ", " << o.b << std::endl;
}