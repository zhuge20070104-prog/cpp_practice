#include <iostream>
#include <functional>
#include <set>
#include <string_view>

class Book {
    friend std::ostream& operator<< (std::ostream& os, const Book& book) {
        os << "[" << book.m_year << ", " << book.m_title << "]";
        return os;
    }

public:
    Book(int year, std::string_view title): m_year{year}, m_title{title} {}

    bool operator< (const Book& right) const {
        return this->m_year < right.m_year;
    }

private:
    int m_year;
    std::string m_title;
};


template <typename Container>
void print_container(const Container& container) {
    auto it {container.begin()};
    while(it != container.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}


class IntComparator {
public:
    bool operator() (int left, int right) const {
        return left < right;
    }
};

bool compare_ints(int left, int right) {
    return left < right;
}

int main(int argc, char* argv[]) {
    std::set<int> s1 {2, 99, 7, 1, 0, -6, 4, 1};
    print_container(s1);

    std::set<Book> book_set {{2011, "CPP Mastery"}, {2001, "C Prog"}};
    print_container(book_set);

    auto it_reverse {s1.rbegin()};
    while(it_reverse != s1.rend()) {
        std::cout << *it_reverse << " ";
        ++it_reverse;
    }
    std::cout << std::endl;

    std::cout << "s1.size(): " << s1.size() << std::endl;
    std::cout << "s1.max_size(): " << s1.max_size() << std::endl;
    std::cout << "s1.empty(): " << s1.empty() << std::endl;

    auto insert_success {s1.insert(5)};
    print_container(s1);

    if(insert_success.second) {
        std::cout << "Inserted: " << *insert_success.first << std::endl;
    } else {
        std::cout << "Not inserted" << std::endl;
    }

    auto emplace_success {s1.emplace(18)};
    if(emplace_success.second) {
        std::cout << "Emplaced: " << *emplace_success.first << std::endl;
    } else {
        std::cout << "Not emplaced" << std::endl;
    }

    print_container(s1);

    std::set<int, std::function<bool(int, int)>> greater_order {[](int left, int right) {
        return left < right;
    }}; 

    greater_order.insert({1, 4, 2, 3, 5});
    print_container(greater_order);

    return EXIT_SUCCESS;
}