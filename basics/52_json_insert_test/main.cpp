#include <nlohmann/json.hpp>
#include <iostream>
#include <cstring>
 
using ordered_json = nlohmann::ordered_json;

struct Person {
    int a;
    char b;
};

int main() {
    Person p {3, 'b'};
    std::vector<uint8_t> buffer(sizeof(Person), 0);
    std::memcpy(buffer.data(), &p, sizeof(Person));
    ordered_json res;
    res["person"] = buffer;
    auto buff_rec = res["person"].get<std::vector<uint8_t>>();
    Person p2;
    std::memcpy(&p2, buff_rec.data(), sizeof(Person));
    std::cout << "a: " << p2.a << " b:" << p2.b << std::endl;
    return 0;
}