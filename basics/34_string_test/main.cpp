#include <string>
#include <regex>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::ifstream ifs("./result.txt");
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string source = ss.str();
    // std::cout << source << std::endl;
    std::smatch result;
    std::string regex_ = R"([\s\S]*?FengHuang planning model([\s\S]*Finished: SUCCESS))";
    std::regex pattern(regex_);
    bool is_matched = std::regex_search(source, result, pattern);
    if (is_matched) {
        std::cout << result.str(1) << std::endl;
    }
    return EXIT_SUCCESS;
}