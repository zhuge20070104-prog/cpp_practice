#include "stopwatch11.h"
#include "kvstruct.h"
#include "test_driver.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <functional>
#include <set>
#include <list>


void build_random_vector(std::vector<kvstruct>& v, unsigned count) {
    std::set<unsigned> unique;
    std::default_random_engine e;
    // 从count 到 10*count的均匀分布
    std::uniform_int_distribution<unsigned> d(count, 10* count);
    auto randomizer = std::bind(d, e);
    v.clear();
    while(v.size() < count) {
        unsigned rv = randomizer();
        // 新元素插入
        if(unique.insert(rv).second == true) {
            v.emplace_back(rv);
        }
    }
}

bool test_vector(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_deque(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_list(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_forward_list(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_map(std::vector<kvstruct> const& random_vector, unsigned long multiplier);
bool test_unordered_map(std::vector<kvstruct> const& random_vector, unsigned long multiplier);


int test_stl(int test_no, unsigned long multiplier) {
    bool rc = true;
    unsigned long table_size = 100000;

    switch (test_no) {
    default:
        return -1;
    case 0: 
        return 2;
    case 1: // 测试kvstruct的各个方法和操作符是否工作
        {
            // 验证10进制转16进制成功
            char buf[9];
            rc &= (strcmp(kvstruct::stringify(0, buf), "0") == 0);
            rc &= (strcmp(kvstruct::stringify(0x123, buf), "123") == 0);
            rc &= (strcmp(kvstruct::stringify(0x1000, buf), "1000") == 0);
            rc &= (strcmp(kvstruct::stringify(0xffffffff, buf), "FFFFFFFF") == 0);

            // 测试build_random_vector返回的值都是唯一的
            std::vector<kvstruct> rnd_vector;
            build_random_vector(rnd_vector, 100);
            std::sort(rnd_vector.begin(), rnd_vector.end());
            for(unsigned i=1; i<rnd_vector.size(); ++i) {
                rc &= (rnd_vector[i-1].key < rnd_vector[i].key);
            }
        }
        break;
    case 2:
        {
            std::vector<kvstruct> rnd_vector;
            build_random_vector(rnd_vector, table_size);

            rc &= test_vector(rnd_vector, multiplier);
            rc &= test_deque(rnd_vector, multiplier);
            rc &= test_list(rnd_vector, multiplier);
            rc &= test_forward_list(rnd_vector, multiplier);
            rc &= test_map(rnd_vector, multiplier);
            rc &= test_unordered_map(rnd_vector, multiplier);
        }
        break;
    }
    return rc ? 1: 0;
}




int main(int argc, char* argv[]) {
    test_driver(test_stl, argc, argv);
    return EXIT_SUCCESS;
}
