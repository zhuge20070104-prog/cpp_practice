#include <iostream>
#include <map>
#include <string>

class Candidate {
public:
    Candidate(std::string const& name=""): m_name(name), m_vote(0) {}

    std::string m_name;
    int m_vote;
};


void print(std::map<char, Candidate> const& m) {
    using IT = std::map<char, Candidate>::const_iterator;
    for(IT it=m.begin(); it!=m.end(); ++it) {
        std::cout << "(" << it->first << "): " 
            << it->second.m_name << ' '; 
    }

    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::map<char, Candidate> m;
    m.insert(std::pair<char, Candidate>('A', Candidate("张飞")));
    m.insert(std::make_pair('B', Candidate("关羽")));
    m['C'] = Candidate("赵云");
    m['D'] = Candidate("马超");
    m['E'] = Candidate("黄忠");
    using IT = std::map<char, Candidate>::iterator;
    for(int i=0; i<10; ++i) {
        print(m);
        char ch;
        std::cin >> ch;
        IT fit = m.find(ch);
        if(fit == m.end()) {
            std::cout << "废票" << std::endl;
            continue;
        }
        ++ (fit->second.m_vote);
    }

    for(IT it = m.begin(); it!=m.end(); ++it) {
        std::cout << it->second.m_name << ":"
            << it->second.m_vote << std::endl;
    }

    return EXIT_SUCCESS;
}