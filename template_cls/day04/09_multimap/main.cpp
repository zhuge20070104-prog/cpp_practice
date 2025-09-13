#include <iostream>
#include <map>
#include <string>

int main(int argc, char* argv[]) {
    std::multimap<std::string, int> m;
    m.insert(std::make_pair("张飞", 80));
    m.insert(std::make_pair("赵云", 70));
    m.insert(std::make_pair("关羽", 60));
    m.insert(std::make_pair("张飞", 50));
    m.insert(std::make_pair("赵云", 40));
    m.insert(std::make_pair("关羽", 30));

    using IT = std::multimap<std::string, int>::const_iterator;
    for(IT it = m.begin(); it!=m.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << std::endl;
    
    return EXIT_SUCCESS;
}