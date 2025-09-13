#ifndef _FREDRIC_FUNCS_H_
#define _FREDRIC_FUNCS_H_

#include <vector>
#include <string>

namespace tn {
namespace integration_test {

std::vector<std::string> str_split(std::string const& input, std::string const& regex);

std::string get_file_content(std::string const& file_path);

void save_to_file(std::string const& file_path, std::string const& content);

}
}
#endif