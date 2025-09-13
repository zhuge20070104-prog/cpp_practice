#include <iostream>
#include "utils/data_extract.h"
#include "utils/data_analysis.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Usage: ./boss_craw {json_dir} {filter_name}" << std::endl;
        std::cerr << "Example: ./boss_craw ./data qa" << std::endl;
        return EXIT_FAILURE;
    }

    std::string json_dir = argv[1];
    std::string filter_name = argv[2];

    data_extract_op_t extract_op {json_dir, filter_name};
    data_extract_t data_extract(extract_op);
    auto job_data = data_extract.do_extract();
    
    data_analysis_t data_analysis(job_data);
    data_analysis.do_analysis();
    std::cout << "Data analysis Done!" << std::endl;
    return EXIT_SUCCESS;
}