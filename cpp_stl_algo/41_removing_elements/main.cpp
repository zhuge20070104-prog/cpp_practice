#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>
#include <algorithm>


template <typename T>
void print_vector(const std::vector<T>& v) {
    std::for_each(std::begin(v), std::end(v), [](const T& elem) {
        std::cout << elem << " ";
    });
    std::cout << std::endl;
}

std::vector<int> source {3, 6, 1, 0, -2, 5};

TEST_CASE("Remove and erase primitive elements") {
   std::vector<int> v(source);
   auto new_end = std::remove(std::begin(v), std::end(v), 3);
   int s = v.size();
   int logical_size = new_end - std::begin(v);
   std::cout << "Size: " << s << ", Logical size: " << logical_size << std::endl;
   print_vector(v);
   v.erase(new_end, std::end(v));
   print_vector(v);

   v = source;
   v.erase(std::remove(std::begin(v), std::end(v), 3), std::end(v));
   print_vector(v);
}


class Resource {
    int i = 1;
public:
    static int object_count;
    Resource();
    Resource(const Resource&);
    Resource& operator=(const Resource&);
    ~Resource();
    void setValue(int ii) {
        i = ii;
    }

    int getValue() const {
        return i;
    }
};


int Resource::object_count = 0;

Resource::Resource() {
    object_count++;
}

Resource::Resource(const Resource& r) {
    i = r.i;
    object_count++;
}

Resource& Resource::operator=(const Resource& r) {
    i = r.i;
    return *this;
}

Resource::~Resource() {
    std::cout << "Destroying Resource: " << i << std::endl;
    object_count--;
}

TEST_CASE("Remove and erase custom elements") {
    std::vector<Resource> vr(2);
    vr[0].setValue(8);
    vr[1].setValue(9);
    auto new_end = std::remove_if(std::begin(vr), std::end(vr), [](const Resource& r) {
        return r.getValue() == 8;
    });

    std::cout << "Object count: " << Resource::object_count << std::endl;
    vr.erase(new_end, std::end(vr));
    std::cout << "Object count: " << Resource::object_count << std::endl;
}