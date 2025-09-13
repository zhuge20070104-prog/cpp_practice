#include "utils/data_extract.h"
#include "utils/funcs.h"

data_extract_t::data_extract_t(data_extract_op_t const& data_ex_op_):
    data_ex_op(data_ex_op_) {}

std::vector<std::string> data_extract_t::get_all_json_files() {
    std::vector<std::string> all_json_files;
    fs::directory_iterator dir_it(data_ex_op.json_dir);
    for(auto const& entry: dir_it) {
        if(entry.path().string().find(data_ex_op.filter_name) != std::string::npos) {
            all_json_files.push_back(entry.path().string());
        }
    }
    return all_json_files;
}

std::vector<job_data_t> data_extract_t::do_extract() {
    auto js_files = get_all_json_files();
    std::vector<job_data_t> result_jobs;

    for(auto const& js_file: js_files) {
        auto js_content = get_file_content(js_file);
        auto result_js = ordered_json::parse(js_content);
        auto& job_list_js = result_js["zpData"]["jobList"];
        for(auto const& job_js: job_list_js) {
            auto job_name = job_js["jobName"].get<std::string>();
            auto& skills_js = job_js["skills"];
            std::vector<std::string> skills;
            for(auto const& skill_js: skills_js) {
                skills.push_back(skill_js.get<std::string>());
            }
            result_jobs.emplace_back(job_name, skills);
        }
    }

    return result_jobs;
}