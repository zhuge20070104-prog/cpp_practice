#include <regex>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string src = "38526 pts/0    00:00:03 sdm\n38526 pts/0    00:00:03 usdm\n";
    std::regex rgx(".*\\s+(usdm).*");
    std::smatch matches;

    if(std::regex_search(src, matches, rgx)) {
        for(auto const& match: matches) {
            std::cout << match.str() << std::endl;
        }
    }
    return EXIT_SUCCESS;
}