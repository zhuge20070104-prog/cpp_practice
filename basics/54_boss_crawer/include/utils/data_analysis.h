#ifndef _FREDRIC_DATA_ANALYSIS_H_
#define _FREDRIC_DATA_ANALYSIS_H_

#include "duckdb.hpp"
#include "beans/beans.h"

struct data_analysis_t {
    data_analysis_t(std::vector<job_data_t> const& job_datas);
    void do_analysis();
private:
    void convert_to_db_data(std::vector<job_data_t> const& job_datas);
    duckdb::DuckDB db;
    duckdb::Connection conn;
};

#endif