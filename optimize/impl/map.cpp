#include "kvstruct.h"
#include "charbuf.h"
#include "stopwatch11.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

bool test_map(std::vector<kvstruct> const& random_vector, unsigned long multiplier) {
    bool rc = true;
    std::size_t const nelts = random_vector.size();
    std::cout << std::endl << "std::map " << random_vector.size() << " entries" << std::endl
        << " multiplier=" << multiplier << std::endl << std::endl;

    using ContainerT = std::map<charbuf<9>, unsigned>;
    using value_type = ContainerT::value_type;
    ContainerT random_container;
    
    for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
        random_container.insert(random_container.end(), value_type(it->key, it->value));
    }

    rc &= random_container.size() == nelts;

    // map insert and delete
    {
        StopWatch::tick_t begin_ticks = 0;
        StopWatch::tick_t assign_ticks = 0;
        StopWatch::tick_t assign_x_1000 = 0;
        StopWatch::tick_t delete_x_1000 = 0;

        {
            StopWatch sw("assign map to map + delete x multiplier");
            ContainerT test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                test_container = random_container;
                assign_ticks = sw.Show("");
                assign_x_1000 += assign_ticks - begin_ticks;
                test_container.clear();
                begin_ticks = sw.Show("");
                delete_x_1000 += begin_ticks - assign_ticks;
            }

            std::cout << "   assign " << assign_x_1000 << "ms"
                << " + delete "
                << delete_x_1000 << "ms"
                << "=="
                << (assign_x_1000 + delete_x_1000)
                << "ms" << std::endl;
        }

        {
            StopWatch sw("vector iterator insert to map + delete x multiplier");
            ContainerT test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
                    test_container.insert(value_type(it->key, it->value));
                }

                test_container.clear();
            }
        }

        std::vector<kvstruct> sorted_vector = random_vector;
        std::stable_sort(sorted_vector.begin(), sorted_vector.end());
        {
            StopWatch sw("sorted vector iterator insert into map + delete x multiplier");
            ContainerT test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                for(auto it=sorted_vector.begin(); it!=sorted_vector.end(); ++it) {
                    test_container.insert(value_type(it->key, it->value));
                }

                test_container.clear();
            }
        }


        {
            StopWatch sw("sorted vector iterator insert into map w/end hint + delete x multiplier");
            ContainerT test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                for(auto it=sorted_vector.begin(); it!=sorted_vector.end(); ++it){
                    test_container.insert(test_container.end(), value_type(it->key, it->value));
                }
                test_container.clear();
            }
        }

        {
            StopWatch sw("sorted vector iterator insert into map w/C++98 preceeder hint + delete x multiplier");
            ContainerT test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                auto hint = test_container.end();
                for(auto it=sorted_vector.begin(); it!=sorted_vector.end(); ++it) {
                    hint = test_container.insert(hint, value_type(it->key, it->value));
                }
            }
            test_container.clear();
        }

        {
            StopWatch sw("sorted vector iterator insert into map w/ reverse iterator follow hint + delete x multiplier");
            ContainerT test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                auto hint = test_container.end();
                for(auto it=sorted_vector.rbegin(); it!=sorted_vector.rend(); ++it) {
                    hint = test_container.insert(hint, value_type(it->key, it->value)); 
                }
                test_container.clear();
            }
        }       
    }

    // map traversal
    ContainerT test_container = random_container;
    
    {
        unsigned long long sum;
        sum = 0;
        {
            StopWatch sw("traverse map (iterator) x multiplier");
            for(unsigned j=0; j<multiplier; ++j) {
                for(auto it=test_container.begin(); it!=test_container.end(); ++it) {
                    sum += it->second;
                }
            }
        }
        rc &= (sum != 0);
    }

    // map lookup 
    {
        StopWatch sw("map lookup x 100");
        for(unsigned j=0; j<100; ++j) {
            for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
                rc &= (test_container.find(it->key) != test_container.end());
                if(test_container.find(it->key) == test_container.end()) {
                    std::cout << "error on key " << it->key << std::endl;
                }
            }
        }
    }
    
    return rc;
}