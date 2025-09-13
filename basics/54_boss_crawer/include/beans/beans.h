#ifndef _FREDRIC_BEANS_H_
#define _FREDRIC_BEANS_H_

#include <string>
#include <vector>

struct data_extract_op_t {
    std::string json_dir;
    std::string filter_name;
};

struct job_data_t {
    job_data_t(std::string const& job_name_, std::vector<std::string> skills_):
      job_name(std::move(job_name_)), skills(std::move(skills_)){}
    std::string job_name;
    std::vector<std::string> skills;
};
#endif