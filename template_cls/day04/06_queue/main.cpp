#include <iostream>
#include <queue>


int main(int argc, char* argv[]) {
    std::queue<int, std::deque<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);

    while(!q.empty()) {
        std::cout << q.front() << std::endl;
        q.pop();
    }
    return EXIT_SUCCESS;
}