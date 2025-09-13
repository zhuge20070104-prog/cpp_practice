#ifndef _FREDRIC_FUNCS_H_
#define _FREDRIC_FUNCS_H_

#include <string>

std::string get_file_content(std::string const& file_path);

void save_to_file(std::string const& file_path, std::string const& content);

#endif