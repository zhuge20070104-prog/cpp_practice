#include <iostream>
#include <deque>


class Item {
public:
    Item(): m_var {0} {}
    explicit Item(int var): m_var{var} {}
    Item(const Item& src) = default;
    int get() const { return m_var; }
private:
    int m_var;
};


std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "Item: " << item.get();
    return os;
}

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
    std::deque<int> my_deque {1, 2, 3, 4, 5};
    std::deque<Item> items_deque {Item{2}, Item{3}, Item{9}};

    print_container(my_deque);
    print_container(items_deque);

    std::cout << "my_deque.front(): " << my_deque.front() << std::endl;
    std::cout << "my_deque.back(): " << my_deque.back() << std::endl;
    
    auto rev_it {my_deque.rbegin()};
    while(rev_it != my_deque.rend()) {
        std::cout << *rev_it << " ";
        ++rev_it;
    }
    std::cout << std::endl;

    std::cout << "my_deque.max_size(): " << my_deque.max_size() << std::endl;
    std::cout << "my_deque.size(): " << my_deque.size() << std::endl;

    my_deque.push_back(22);
    std::cout << "my_deque.size(): " << my_deque.size() << std::endl;

    auto it_begin {my_deque.begin() + 2};

    my_deque.insert(it_begin, 100);

    print_container(my_deque);

    std::cout << "*it_begin: " << *it_begin << std::endl;
    
    return EXIT_SUCCESS;    
}
