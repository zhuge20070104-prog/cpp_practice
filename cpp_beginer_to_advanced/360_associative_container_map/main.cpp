#include <iostream>
#include <functional>
#include <map>
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

class IntComparator {
public:
    bool operator()(int left, int right) const {
        return left < right;
    }
};

bool compare_ints(int left, int right) {
    return left < right;
}


template <typename T, typename K>
void print_map(const std::map<T, K>& map) {
    auto it {map.begin()};
    while(it != map.end()) {
        std::cout << it->first << ", " << it->second << std::endl;
        ++it;
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::map<int, int> map1 {{11, 101}, {2, 202}, {3, 303}, {4, 404}};

    std::map<int, Book> book_map1 {{1, {2021, "Book1"}},
                                   {0, {1992, "Book2"}},
                                   {8, {2002, "Book3"}}};

    print_map(map1);
    print_map(book_map1);

    for(const auto& [key, value]: book_map1) {
        std::cout << key << ", " << value << std::endl;
    }
    std::cout << std::endl;

    std::map<std::string, std::string> string_map {
        {"Dan", "NY"}, {"Juda", "LA"}, {"Caleb", "TX"}
    };

    print_map(string_map);

    auto it {string_map.begin()};
    while(it != string_map.end()) {
        std::cout << (*it).first << ", " << (*it).second << std::endl;
        ++it;
    }
    std::cout << std::endl;

    auto it_reverse {string_map.rbegin()};
    while(it_reverse != string_map.rend()) {
        std::cout << (*it_reverse).first << ", " << (*it_reverse).second << std::endl;
        ++it_reverse;
    }
    std::cout << std::endl;

    it = string_map.begin();
    while(it != string_map.end()) {
        string_map[it->first] = "something";
        ++it;
    }
    print_map(string_map);


    std::cout << "string_map.size(): " << string_map.size() << std::endl;
    std::cout << "string_map.max_size(): " << string_map.max_size() << std::endl;
    std::cout << "string_map.empty(): " << string_map.empty() << std::endl;

    auto result {string_map.insert({"new", "data"})};
    if(result.second) {
        std::cout << "Inserted: " << result.first->first << ", " << result.first->second << std::endl;
    }

    auto emplace_result {string_map.emplace("new data", "again")};
    if(emplace_result.second) {
        std::cout << "Emplaced: " << emplace_result.first->first << ", " << emplace_result.first->second << std::endl;
    }

    
    std::map<int, int, std::function<bool(int, int)>> lambda_map([](int left, int right) {
        return left > right;
    });

    lambda_map.insert({{11, 2}, {3, 4}});

    auto int_it {lambda_map.begin()};
    while(int_it != lambda_map.end()) {
        std::cout << int_it->first << ", " << int_it->second << std::endl;
        ++int_it;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}