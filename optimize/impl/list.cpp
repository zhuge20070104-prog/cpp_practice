#include "stopwatch11.h"
#include "kvstruct.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

// TODO: add test_list code
bool test_list(std::vector<kvstruct> const& random_vector, unsigned long multiplier) {
    bool rc = true;
    std::size_t const nelts = random_vector.size();
    std::cout << std::endl << "std::list " << random_vector.size() << " entries" << std::endl
        << "multiplier == " << multiplier << std::endl << std::endl;

    std::list<kvstruct> random_container; 
    // list insert and delete
    {
        random_container.insert(random_container.end(), random_vector.begin(), random_vector.end());

        {
            StopWatch sw("assign list to list + delete x multiplier");
            StopWatch::tick_t begin_ticks = 0;
            StopWatch::tick_t assign_ticks = 0;
            StopWatch::tick_t assign_x_1000 = 0;
            StopWatch::tick_t delete_x_1000 = 0;

            std::list<kvstruct> test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                test_container = random_container;
                assign_ticks = sw.Show("");
                assign_x_1000 += assign_ticks - begin_ticks;
                test_container.clear();
                begin_ticks = sw.Show("");
                delete_x_1000 += begin_ticks - assign_ticks;
            }

            std::cout << "assign " << assign_x_1000 << "ms"
                << "    + delete "
                << delete_x_1000 << "ms"
                << " == " << (assign_x_1000 + delete_x_1000)
                << "ms" << std::endl;
        }

        {
            StopWatch sw("vector iterator insert(end()) + delete x multiplier");
            std::list<kvstruct> test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                test_container.insert(test_container.end(), random_vector.begin(), random_vector.end());
                test_container.clear();
            }
        }

        {
            StopWatch sw("vector iterator push_back() + delete x multiplier");
            std::list<kvstruct> test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
                    test_container.push_back(*it);
                }
                test_container.clear();
            }
        }

        {
            StopWatch sw("vector at() push_back + delete x multiplier");
            std::list<kvstruct> test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<nelts; ++i) {
                    test_container.push_back(random_vector.at(i));
                }

                test_container.clear();
            }
        }

        {
            StopWatch sw("vector[] push_back + delete x multiplier");
            std::list<kvstruct> test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                for(unsigned i=0; i<nelts; ++i) {
                    test_container.push_back(random_vector[i]);
                }
                test_container.clear();
            }
        }

        {
            StopWatch sw("vector iterator push_front() + delete multiplier");
            std::list<kvstruct> test_container;
            for(unsigned j=0; j<multiplier; ++j) {
                for(auto it=random_vector.begin(); it!=random_vector.end(); ++it) {
                    test_container.push_front(*it);
                }
                test_container.clear();
            }
        }

        {   StopWatch sw("vector.at() push_front() + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_front(random_vector.at(i));
				test_container.clear();
			}
		}
		{   StopWatch sw("vector[] push_front() + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.push_front(random_vector[i]);
				test_container.clear();
			}
		}

		{   StopWatch sw("vector iterator insert at back + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(test_container.end(), *it);
				test_container.clear();
			}
		}
		{   StopWatch sw("vector.at() insert at end + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.end(), random_vector.at(i));
				test_container.clear();
			}
		}
		{   StopWatch sw("vector[] insert at end + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.end(), random_vector[i]);
				test_container.clear();
			}
		}

		{   StopWatch sw("vector iterator insert at last position + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				auto place = test_container.begin();
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					place = test_container.insert(place, *it);
				test_container.clear();
			}
		}

		{   StopWatch sw("vector iterator insert at front + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (auto it = random_vector.begin(); it != random_vector.end(); ++it)
					test_container.insert(test_container.begin(), *it);
				test_container.clear();
			}
		}
		{   StopWatch sw("vector.at() insert at front + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.begin(), random_vector.at(i));
				test_container.clear();
			}
		}
		{   StopWatch sw("vector[] insert at frone + delete x multiplier");
			std::list<kvstruct> test_container;
			for (unsigned j = 0; j < multiplier; ++j) {
				for (unsigned i = 0; i < nelts; ++i)
					test_container.insert(test_container.begin(), random_vector[i]);
				test_container.clear();
			}
		}
    }

    //	traversal
	{
		std::list<kvstruct> test_container;
		unsigned long long sum;
		sum = 0;
		test_container = random_container;
		{   StopWatch sw("traverse list (iterator) x 1000");
			for (unsigned j = 0; j < 1000; ++j)
				for (auto it = test_container.begin(); it != test_container.end(); ++it)
					sum += it->value;
		}
		rc &= (sum != 0);
    }

    //	list sort
	{
		std::list<kvstruct> sorted_container;
		{	StopWatch sw("std::list::sort() list + build + delete x 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container = random_container;
				sorted_container.sort();
			}
		}
		{	StopWatch sw("std::list::sort() sorted list x 100");
			for (unsigned j = 0; j < 100; j++) {
				sorted_container.sort();
			}
		}
		rc &= (sorted_container.size() == random_vector.size());
	}

    return rc;
}