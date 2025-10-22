#include <iostream>
#include <forward_list>

template <typename Container>
void print_container(const Container& container) {
    auto it {container.begin()};
    while(it != container.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::forward_list<int> f_list {2, 4, 8, 10, 12};
    print_container(f_list);

    std::cout << "f_list.front(): " << f_list.front() << "\n";
    
    auto before_it {f_list.before_begin()};
    f_list.insert_after(before_it, 0);
    print_container(f_list);

    f_list.emplace_after(before_it, 1);
    print_container(f_list);

    f_list.pop_front();
    f_list.pop_front();

    print_container(f_list);

    f_list.resize(3);
    print_container(f_list);

    f_list.resize(5);
    print_container(f_list);

    std::forward_list<int> f_list2 {10, 20};
    f_list.merge(f_list2);
    std::cout << "f_list: ";
    print_container(f_list);
    std::cout << "f_list2: ";
    print_container(f_list2);


    f_list.clear();
    f_list2.clear();

    f_list = {1, 2, 3, 4, 5};
    f_list2 = {3, 6, 10, 8, 13, 20, 9, 4};

    f_list.splice_after(f_list.before_begin(), f_list2, f_list2.before_begin(), f_list2.end());
    std::cout << "================================================" << std::endl;
    std::cout << "After splice:f_list: ";
    print_container(f_list);
    std::cout << "f_list2: ";
    print_container(f_list2);
    std::cout << "================================================" << std::endl;

    f_list.remove(3);
    print_container(f_list);

    f_list.remove_if([](int n) {
        return n > 5;
    });

    print_container(f_list);

    f_list.reverse();
    print_container(f_list);

    f_list = { 2, 2, 1, 2, 3 };
    print_container(f_list);

    f_list.unique();
    print_container(f_list);

    f_list.sort();
    print_container(f_list);

    return EXIT_SUCCESS;    
}
