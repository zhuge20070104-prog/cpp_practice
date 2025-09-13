#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <set>


template <typename T>
bool are_elements_in(std::vector<T> const& vec_exp, std::vector<T> const& vec_act) {
    for(auto const& exp_ele: vec_exp) {
        if(std::find(vec_act.begin(), vec_act.end(), exp_ele) == vec_act.end()) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> vec_act {"a", "b", "c", "e"};
    std::vector<std::string> vec_exp {"a", "b", "c", "d"};

    using TestCaseType = std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>;
    
    TestCaseType cases = {
        {{"a", "b", "c", "d"}, {"a", "b", "c", "e"}},  // expect, actual
        {{"a", "b", "c", "e"}, {"a", "b", "c", "e"}},
        {{"a", "b", "c"}, {"a", "b", "c", "e"}},
        {{"a", "e", "b", "c"}, {"a", "b", "c", "e"}},
    };

    std::vector<bool> results = {
        false,
        true,
        true,
        true
    };

    std::cout << "Test started =======================================" << std::endl;
    for(int i=0; i<cases.size(); ++i) {
        if(are_elements_in(cases[i].first, cases[i].second) != results[i]) {
            std::cerr << "Case [" << i << "] failed!" << std::endl;
        }
    }
    std::cout << "Test end ===========================================" << std::endl;


    std::set<int> v_all {0, 1, 2, 3, 4};
    std::set<int> v_child {3, 1};
    std::list<int> v_result {};
    v_result.resize(v_all.size(), -1);
    std::set_difference(v_all.begin(), v_all.end(), v_child.begin(), v_child.end(), v_result.begin());
    
    v_result.remove(-1);
    std::cout << "v_result.size(): " << v_result.size() << std::endl;
    for(auto const& v: v_result) {
        std::cout << v << std::endl;
    }

    return EXIT_SUCCESS;
}