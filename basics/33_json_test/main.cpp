#include "json.hpp"
#include <iostream>

using ordered_json = nlohmann::ordered_json;

void update_json_by_ptr(ordered_json const* src_js, ordered_json* result_js) {
    ordered_json tmp = *src_js;
    tmp["sequences"][0]["name"] = "Lily";
    for(auto & js: tmp["sequences"]) {
        (*result_js)["sequences"].push_back(js);
    }
}
int main(int argc, char* argv[]) {
    std::string js_s = R"(
        {"sequences": [{"name": "ZhangSan", "age": 24}] }
    )"; 

    ordered_json src = ordered_json::parse(js_s);
    ordered_json res_js;
    res_js["sequences"] = ordered_json::array();
    update_json_by_ptr(&src, &res_js);
    update_json_by_ptr(&src, &res_js);
    std::cout << "In main src: " << src.dump(4) << "\n";
    std::cout << "In main res: " << res_js.dump(4) << "\n";
    return EXIT_SUCCESS;
}