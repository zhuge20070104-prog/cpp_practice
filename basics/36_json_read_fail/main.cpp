#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include <string>
#include <set>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


int main(int argc, char* argv[]) {
    
    auto js_s = R"([{
        "name": "ZhangSan",
        "age": 23,
    }])";

    auto js = json::parse(js_s, nullptr, false);
    std::cout << std::boolalpha << js.is_discarded() << std::endl;


    return EXIT_SUCCESS;
}