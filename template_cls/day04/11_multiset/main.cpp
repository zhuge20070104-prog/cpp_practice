#include <iostream>
#include <set>


int main(int argc, char* argv[]) {
    std::multiset<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(1);
    s.insert(2);
    s.insert(3);

    std::cout << "节点个数:" << s.size() << std::endl;

    using IT = std::multiset<int>::iterator;
    for(IT it=s.begin(); it!=s.end(); ++it) {
        std::cout << *it << ' '; 
    }

    std::cout << std::endl;
    
    return EXIT_SUCCESS;
}