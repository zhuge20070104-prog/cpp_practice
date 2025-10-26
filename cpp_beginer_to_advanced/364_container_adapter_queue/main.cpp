#include <iostream>
#include <queue>
#include <list>
#include <deque>


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


template <typename T, typename Container = std::deque<T>>
void print_queue(std::queue<T, Container> queue_) {
    std::cout << "Queue: [";
    while(!queue_.empty()) {
        std::cout << queue_.front() << " ";
        queue_.pop();
    }
    std::cout << "]" << std::endl;
}


template <typename T, typename Container = std::deque<T>>
void clear_queue(std::queue<T, Container>& queue_) {
    while(!queue_.empty()) {
        queue_.pop();
    }
}


int main(int argc, char* argv[]) {
    std::queue<int> queue1;

    queue1.push(6);
    queue1.push(8);
    queue1.push(4);
    queue1.push(1);
    queue1.push(3);

    print_queue(queue1);

    std::cout << queue1.front() << ' ' << queue1.back() << std::endl;

    queue1.front() = 66;
    queue1.back() = 33;

    print_queue(queue1);

    queue1.pop();
    print_queue(queue1);

    clear_queue(queue1);
    std::cout << "Size becomes: " << queue1.size() << std::endl;

    print_queue(queue1);


    std::queue<Book> books;
    books.push({2021, "Book1"});
    books.push({1992, "Book2"});
    books.push({1886, "Book3"});

    print_queue(books);

    std::queue<int, std::list<int>> list_queue;

    list_queue.push(2);
    list_queue.push(3);
    print_queue(list_queue);

    return EXIT_SUCCESS;
}