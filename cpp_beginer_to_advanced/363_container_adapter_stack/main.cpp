#include <iostream>
#include <functional>
#include <stack>
#include <vector>
#include <deque>


template <typename T>
void print_stack(std::stack<T> stack) {
    std::cout << "Stack: [";
    
    while(!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    
    std::cout << "]" << std::endl;
}


template <typename T, typename Container = std::deque<T>>
void print_vstack(std::stack<T, Container> stack) {
    std::cout << "Stack: [";
    while(!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << "]" << std::endl;
}


template <typename T>
void clear_stack(std::stack<T>& stack) {
    while(!stack.empty()) {
        stack.pop();
    }
}

template <typename T, typename Container = std::deque<T>>
void clear_vstack(std::stack<T, Container>& stack) {
    while(!stack.empty()) {
        stack.pop();
    }
}


int main(int argc, char* argv[]) {
    std::stack<int> stack1 {};
    print_stack(stack1);

    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    print_stack(stack1);

    std::cout << "Top: " << stack1.top() << std::endl;

    stack1.top() = 5;

    print_stack(stack1);

    stack1.pop();

    print_stack(stack1);
    clear_stack(stack1);
    print_stack(stack1);


    std::stack<int, std::vector<int>> vstack1 {};
    vstack1.push(11);
    vstack1.push(22);
    vstack1.push(33);
    print_vstack(vstack1);
    clear_vstack(vstack1);
    print_vstack(vstack1);
    
    return EXIT_SUCCESS;
}