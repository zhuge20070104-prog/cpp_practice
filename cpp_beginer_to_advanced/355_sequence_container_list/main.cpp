#include <iostream>
#include <list>


template <typename Container>
void print_container(const Container& container) {
    auto it {container.begin()};
    while(it != container.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

// insert/emplace 在 iterator 前面插入
// insert_after/emplace_after 在 iterator 后面插入
int main(int argc, char* argv[]) {
    std::list<int> list {1, 12, 36, 8, 10};
    print_container(list);
    
    std::cout << "list.front(): " << list.front() << std::endl;
    std::cout << "list.back(): " << list.back() << std::endl;

    auto it_reverse {list.rbegin()};
    while(it_reverse != list.rend()) {
        std::cout << *it_reverse << " ";
        ++it_reverse;
    }
    std::cout << std::endl;
    
    std::cout << "list.max_size(): " << list.max_size() << std::endl;
    std::cout << "list.size(): " << list.size() << std::endl;
    std::cout << "list.empty(): " << list.empty() << std::endl;

    auto it_insert {std::find(list.begin(), list.end(), 36)};

    list.insert(it_insert, 20);
    print_container(list);

    list.pop_back();
    print_container(list);

    list.emplace(list.begin(), 19);
    print_container(list);

    list.push_front(22);
    print_container(list);

    list.resize(5);
    print_container(list);

    list.resize(10);
    print_container(list);

    list.resize(4);
    print_container(list);
    return EXIT_SUCCESS;    
}
