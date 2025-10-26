#include <iostream>
#include <queue>
#include <vector>


template <typename T>
void print_queue(std::priority_queue<T> queue_) {
    std::cout << "Priority Queue: [";
    while(!queue_.empty()) {
        std::cout << queue_.top() << " ";
        queue_.pop();
    }
    std::cout << "]" << std::endl;
}


template <typename T, typename Container = std::vector<T>,
    typename Compare = std::less<typename Container::value_type>>
void print_vqueue(std::priority_queue<T, Container, Compare> queue_) {
    std::cout << "Priority Queue: [";
    while(!queue_.empty()) {
        std::cout << queue_.top() << " ";
        queue_.pop();
    }
    std::cout << "]" << std::endl;
}

template <typename T, typename Container = std::vector<T>,
    typename Compare = std::less<typename Container::value_type>>
void clear_vqueue(std::priority_queue<T, Container, Compare>& queue_) {
    while(!queue_.empty()) {
        queue_.pop();
    }
}


int main(int argc, char* argv[]) {
    std::priority_queue<int> queue1;
    queue1.push(2);
    queue1.push(6);
    queue1.push(3);
    queue1.push(1);
    print_queue(queue1);


    queue1.pop();
    print_queue(queue1);
    clear_vqueue(queue1);
    print_queue(queue1);


    std::priority_queue<int, std::vector<int>, std::greater<int>> queue2;
    queue2.push(1);
    queue2.push(8);

    print_vqueue(queue2);

    auto compare {[](int left, int right) {
        return left < right;
    }};

    std::priority_queue<int, std::vector<int>, decltype(compare)> queue3 {compare};
    queue3.push(2);
    queue3.push(8);
    queue3.push(3);
    print_vqueue(queue3);

    return EXIT_SUCCESS;
}