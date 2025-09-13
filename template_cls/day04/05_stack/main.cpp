#include <stack>
#include <iostream>


int main(int argc, char* argv[]) {
    std::stack<int, std::deque<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
    while(!s.empty()) {
        std::cout << s.top() << std::endl;
        s.pop();
    }
    return EXIT_SUCCESS;
}