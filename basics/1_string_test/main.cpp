#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string json_path = "./test_result/path1/result.htm";
    auto result_js_path = json_path.substr(0, json_path.length()-3);
    result_js_path += "json";
    std::cout << result_js_path << std::endl;
 
    return EXIT_SUCCESS;
}