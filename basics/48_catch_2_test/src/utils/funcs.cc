#include <regex>
#include <sstream>
#include <fstream>

namespace tn {
namespace integration_test {

std::vector<std::string> str_split(std::string const& input, std::string const& regex) {
    std::regex re(regex);
    std::sregex_token_iterator
        first{input.begin(), input.end(), re, -1},
        last;
    return {first, last};
}

std::string get_file_content(std::string const& file_path) {
    std::ifstream ifs(file_path );
    std::stringstream file_ss;
    file_ss <<  ifs.rdbuf(); 
    std::string document = file_ss.str();
    ifs.close();
    return document;
}

void save_to_file(std::string const& file_path, std::string const& content) {
    std::fstream fs(file_path, std::ios::out);
    fs << content;
    fs.flush();
    fs.close();
}

}
}
