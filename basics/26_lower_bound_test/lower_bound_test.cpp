#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>

int main(int argc, char* argv[]) {
    std::vector<int> rand_eles {10, 8, 7, 9 ,5, 6, 1, 3, 2, 4, 14, 13, 12, 11, 15};
    std::vector<int> sorted_eles {1, 2, 3, 4, 5, 6 ,7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<int>::iterator kp;
    for(auto it=rand_eles.begin(); it!=rand_eles.end(); ++it) {
        kp = std::lower_bound(sorted_eles.begin(),
                                                        sorted_eles.end(),
                                                        *it);
        if(kp!=sorted_eles.end() && *it < *kp) {
            std::cout << "Reset to end\n";
            kp = sorted_eles.end();
        }
     }

    std::cout << std::boolalpha << (kp!=sorted_eles.end()) << "\n";
    return EXIT_SUCCESS;
}