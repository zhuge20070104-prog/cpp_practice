#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <cassert>
#include "asyc_out.hpp"


struct List {
    struct Node {
        int value;
        Node* next;

        Node(int value_):
            value(value_), next(nullptr) {}
    };

    // List
    Node* head;
    List(): head(nullptr) {}
    void insert(int x) {
        auto node = new Node(x);
        node->next = head;
        head = node;
    }

    int count() const {
        int n {0};
        auto cur = head;
        while(cur != nullptr) {
            ++n;
            cur = cur->next;
        }
        return n;
    }
};

// Race的过程可以参考
// https://note.youdao.com/s/XME5s8x
void the_func(List& list) {
    for(int i=0; i<100; ++i) {
        list.insert(i);
    }
}

int main(int argc, char* argv[]) {  
    List list;
    std::vector<std::thread> workers;
    for(int i=0; i<10; ++i) {
        workers.push_back(std::thread(&the_func, std::ref(list)));
    }

    std::for_each(workers.begin(), workers.end(), [](std::thread& th) {
        th.join();
    });

    int total = list.count();
    std::cout << "List count: " << total << "\n"; 
    return EXIT_SUCCESS;
}