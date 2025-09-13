#include <iostream>
#include <vector>
#include <map>
#include <cstring>


std::vector<std::pair<const void*, std::size_t>> msgs;

int main(int argc, char* argv[]) {
    int a = 10;
    double b = 100.0;
    int c = 20;

    msgs.push_back({&a, 4});
    msgs.push_back({&b, 8});
    msgs.push_back({&c, 4});

    for(auto& item: msgs) {
        if(item.second == 8) {
            double val;
            memcpy(&val, item.first, sizeof(double));
            std::cout << val << std::endl; 
        } else {
            int val;
            memcpy(&val, item.first, sizeof(int));
            std::cout << val << std::endl;  
        }
    }

}