#include "stopwatch11.h"
#include "kvstruct.h"

#include <iostream>
#include <algorithm>
#include <vector>

bool test_vector(std::vector<kvstruct> const& random_vector, unsigned long multiplier) {
    bool rc = true;
    std::size_t const nelts = random_vector.size();

    std::cout << std::endl << "std::vector  " << random_vector.size() << " entries" << std::endl << std::endl;

    // std::vector 插入和删除
    {
        StopWatch sw("assign vector to vector + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<multiplier; ++j) {
            test_container = random_vector;
            std::vector<kvstruct>().swap(test_container);
        }
    }
    
    // 1000 次的插入和删除统计 
    {   
        StopWatch sw("assign vector to vector", false);
        StopWatch::tick_t ticks;
        StopWatch::tick_t assign_x_1000 = 0;
        StopWatch::tick_t delete_x_1000 = 0;
        std::vector<kvstruct> test_container;

        for(unsigned j=0; j<1000; ++j) {
            sw.Start("");
            test_container = random_vector;
            ticks = sw.Show("");
            assign_x_1000 += ticks;

            std::vector<kvstruct>().swap(test_container);
            delete_x_1000 += sw.Stop("") - ticks;
        }

        std::cout << "  assign vector to vector x 1000: " 
            << assign_x_1000 << "ms" << std::endl;
        
        std::cout << "  vector delete x 1000: "
            << delete_x_1000 << "ms" << std::endl;
    }

    // std::vector 迭代器插入加删除1000次
    {
        StopWatch sw("vector iterator insert(begin()) vector + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            test_container.insert(test_container.begin(), random_vector.begin(), random_vector.end());
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("same, only with reserve");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            test_container.reserve(nelts);
            test_container.insert(test_container.begin(), random_vector.begin(), random_vector.end());
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("vector iterator insert(end()) vector + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            test_container.insert(test_container.end(), random_vector.begin(), random_vector.end());
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("vector iterator push_back() to vector + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            for(auto it=random_vector.begin(); it != random_vector.end(); ++it) {
                test_container.push_back(*it);
            }
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("same, only with reserve");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            test_container.reserve(nelts);
            for(auto it=random_vector.begin(); it != random_vector.end(); ++it) {
                test_container.push_back(*it);
            }
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("vector.at() push_back() to vector + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            for(unsigned i=0; i<nelts; ++i) {
                test_container.push_back(random_vector.at(i));
            }

            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("vector[] push_back() to vector + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            for(unsigned i=0; i<nelts; ++i) {
                test_container.push_back(random_vector[i]);
            }
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("vector iterator insert at back to vector + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
                test_container.insert(test_container.end(), *it);
            }
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("same, but with reserve");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            test_container.reserve(nelts);
            for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
                test_container.insert(test_container.end(), *it);
            }
            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("vector.at() insert at end + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            for(unsigned i=0; i<nelts; ++i) {
                test_container.insert(test_container.end(), random_vector.at(i));
            }

            std::vector<kvstruct>().swap(test_container);
        }
    }

    {
        StopWatch sw("vector[] insert at the end + delete x 1000");
        std::vector<kvstruct> test_container;
        for(unsigned j=0; j<1000; ++j) {
            for(unsigned i=0; i<nelts; ++i) {
                test_container.insert(test_container.end(), random_vector[i]);
            }
            std::vector<kvstruct>().swap(test_container);
        }
    }

    // vector insert at front part 
    std::vector<kvstruct> test_container;
    {
        StopWatch sw("vector interator insert at front to vector");
        for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
            test_container.insert(test_container.begin(), *it);
        }
    }

    std::vector<kvstruct>().swap(test_container);
    {
        StopWatch sw("same but with reserve");
        test_container.reserve(nelts);
        for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
            test_container.insert(test_container.begin(), *it);
        }
    }

    std::vector<kvstruct>().swap(test_container);
    {
        StopWatch sw("vector at() insert at front");
        for(unsigned i=0; i<nelts; ++i) {
            test_container.insert(test_container.begin(), random_vector.at(i));
        }
    }

    std::vector<kvstruct>().swap(test_container);
    {
        StopWatch sw("vector [] insert at front");
        for(unsigned i=0; i<nelts; ++i) {
            test_container.insert(test_container.begin(), random_vector[i]);
        }
    }


    // vector traversal
    {
        long long sum;
        std::vector<kvstruct> test_container = random_vector;

        sum = 0;
        {
            StopWatch sw("traversal vector (at) x 1000");
            for(unsigned j=0; j<1000; ++j) {
                for(unsigned i=0; i<nelts; ++i) {
                    sum += test_container.at(i).value;
                }
            }
        }
        rc &= (sum!=0);

        sum = 0;
        {
            StopWatch sw("traversal vector, subscript, size() x 1000");
            for(unsigned j=0; j<1000; ++j) {
                for(unsigned i=0; i<test_container.size(); ++i) {
                    sum += test_container[i].value;
                }
            }
        }

        rc &= (sum!=0);

        sum = 0;
        {
            StopWatch sw("traversal vector (subscript) x 1000");
            for(unsigned j=0; j<1000; ++j) {
                for(unsigned i=0; i<nelts; ++i) {
                    sum += test_container[i].value;
                }
            }
        }

        rc &= (sum!=0);

        sum = 0;
        {
            StopWatch sw("traversal vector (iterator) x 1000");
            for(unsigned j=0; j<1000; ++j) {
                for(auto it=test_container.begin(); it!=test_container.end(); ++it) {
                    sum += it->value;
                }
            }
        }

        rc &= (sum!=0);
    }

    // vector sort
    {
        std::vector<kvstruct> sorted_container;
        sorted_container = random_vector;

        {
            StopWatch sw("std::sort() vector + assign + delete x 100");
            for(unsigned j=0; j<100; ++j) {
                sorted_container = random_vector;
                std::sort(sorted_container.begin(), sorted_container.end());
            }
        }

        {
            StopWatch sw("std::sort() sorted vector x 100");
            for(unsigned j=0; j<100; ++j) {
                std::sort(sorted_container.begin(), sorted_container.end());
            }
        }
        rc &= (sorted_container.size() == random_vector.size());

        // std::stable_sort
        sorted_container = random_vector;
        {
            StopWatch sw("std::stable_stort() vector assign + delete x 100");
            for(unsigned j=0; j<100; ++j) {
                sorted_container = random_vector;
                std::stable_sort(sorted_container.begin(), sorted_container.end());
            }
        }

        {
            StopWatch sw("std::stable_sort() sorted vector x 100");
            for(unsigned j=0; j<100; ++j) {
                std::stable_sort(sorted_container.begin(), sorted_container.end());
            }
        }

        rc &= (sorted_container.size() == random_vector.size());
    }

    // lookup
    {
        std::vector<kvstruct> sorted_container;
        sorted_container = random_vector;
        std::sort(sorted_container.begin(), sorted_container.end());

        StopWatch sw("lookup in sorted vector x 100");

        std::vector<kvstruct>::iterator kp;
        for(unsigned j=0; j<100; ++j) {
            for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
                kp = std::lower_bound(sorted_container.begin(), sorted_container.end(),
                    *it);
                // 不可能有小于的，因为random_vector中的值都是 sorted_container中的值，都是
                // *it == *kp
                if(kp!= sorted_container.end() && *it < *kp) {
                    kp = sorted_container.end();
                }
            }
        }

        rc &= (kp != sorted_container.end());
    }
    
    return rc;
}


