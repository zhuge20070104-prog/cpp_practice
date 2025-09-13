#ifndef _FREDRIC_DATA_EXTRACT_H_
#define _FREDRIC_DATA_EXTRACT_H_

#include "nlohmann/json.hpp"
#include "boost/filesystem.hpp"
#include "beans/beans.h"
#include <string>
#include <vector>

using ordered_json = nlohmann::ordered_json;
namespace fs = boost::filesystem;


struct data_extract_t {
    data_extract_t(data_extract_op_t const& data_ex_op_);
    std::vector<job_data_t> do_extract();
private:
    std::vector<std::string> get_all_json_files();
    data_extract_op_t data_ex_op;
};
#endif