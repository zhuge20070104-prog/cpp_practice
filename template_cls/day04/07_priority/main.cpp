#include <iostream>
#include <queue>


class CMP {
public:
    bool operator()(int const& a, int const& b) {
        return a > b;
    }
};


int main(int argc, char* argv[]) {
    std::priority_queue<int, std::deque<int>, CMP> pq;
    pq.push(3);
    pq.push(8);
    pq.push(4);
    pq.push(9);
    pq.push(5);
    pq.push(7);

    while(!pq.empty()) {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
    return EXIT_SUCCESS;
}