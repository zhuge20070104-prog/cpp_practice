#include "utils/funcs.h"
#include <fstream>
#include <sstream>
#include <string>

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
