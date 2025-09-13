#include "utils/data_analysis.h"
#include <sstream>

data_analysis_t::data_analysis_t(std::vector<job_data_t> const& job_datas):
    db(nullptr), conn(db) {
    convert_to_db_data(job_datas);
}

void data_analysis_t::do_analysis() {
    std::string skills_analysis_query = R"(copy(select skill, count(skill) as skill_count from
        (select unnest(skills) as skill  from job) group by skill order by skill_count desc) 
        to 'analysis.csv' (HEADER, DELIMITER ',');)";
    conn.Query(skills_analysis_query);
    
    std::string raw_result_query = R"(copy(select * from job) 
        to 'job.csv' (HEADER, DELIMITER ',');)";
    conn.Query(raw_result_query);
}

void data_analysis_t::convert_to_db_data(std::vector<job_data_t> const& job_datas) {
    conn.Query("CREATE TABLE job (job_name VARCHAR, skills VARCHAR[])");
    for(auto const& job_data: job_datas) {
        std::stringstream insert_job_data_ss;
        insert_job_data_ss << "INSERT INTO job VALUES('" << job_data.job_name << "', [";
        std::stringstream skill_ss;
        for(auto const& skill: job_data.skills) {
            skill_ss << "'";
            skill_ss << skill;
            skill_ss << "'";
            skill_ss << ",";
        }
        std::string skill_str = skill_ss.str();
        skill_str = skill_str.substr(0, skill_str.size() - 1);
        
        insert_job_data_ss << skill_str;
        insert_job_data_ss << "]);";
        conn.Query(insert_job_data_ss.str());
    }
}