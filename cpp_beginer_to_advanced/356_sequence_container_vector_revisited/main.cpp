#include <iostream>
#include <vector>


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
    std::vector<int> int_vector {1, 2, 3, 4, 5};
    print_container(int_vector);

    std::cout << "int_vector[1]: " << int_vector[1] << std::endl;
    std::cout << "int_vector.at(1): " << int_vector.at(1) << std::endl;
     
    // std::cout << "int_vector[22]: " << int_vector[22] << std::endl; // no bounds checking - 危险！越界访问

    std::cout << "int_vector.front(): " << int_vector.front() << std::endl;
    std::cout << "int_vector.back(): " << int_vector.back() << std::endl;
    
    // return a pointer to the underlying data
    std::cout << "*(int_vector.data()): " << *(int_vector.data()) << std::endl;

    // reverse iterator
    auto it_reverse {int_vector.rbegin()};
    while(it_reverse != int_vector.rend()) {
        std::cout << *it_reverse << " ";
        ++it_reverse;
    }
    std::cout << std::endl;

    std::cout << "int_vector.max_size(): " << int_vector.max_size() << std::endl;
    std::cout << "int_vector.size(): " << int_vector.size() << std::endl;
    std::cout << "int_vector.capacity(): " << int_vector.capacity() << std::endl;
    std::cout << "int_vector.empty(): " << int_vector.empty() << std::endl;

    // 正确做法：insert返回指向新插入元素的迭代器，需要接收它
    auto it_insert {int_vector.begin() + 1};
    it_insert = int_vector.insert(it_insert, 22);  // 更新迭代器
    std::cout << "After insert 22: *it_insert: " << *it_insert << std::endl;
    it_insert = int_vector.insert(it_insert, 33);  // 更新迭代器
    std::cout << "After insert 33: *it_insert: " << *it_insert << std::endl;
    it_insert = int_vector.insert(it_insert, 44);  // 更新迭代器
    std::cout << "After insert 44: *it_insert: " << *it_insert << std::endl;
    
    print_container(int_vector);

    int_vector.erase(int_vector.begin(), int_vector.begin() + 2);
    int_vector.erase(int_vector.begin() + 1);

    print_container(int_vector);
  
    return EXIT_SUCCESS;    
}
