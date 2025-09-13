#include "boost/program_options.hpp"
#include <iostream>

namespace opt = boost::program_options;

int main(int argc, char* argv[]) {
    opt::options_description desc("All Options");
    desc.add_options()
        ("help,h", "Produce help message")
        ("lcov", "Whether to run lcov in integration test mode, default not run")
        ("config.path", opt::value<std::string>()->default_value("./integration_test.cfg"), "The configuration file path")
        ("run.mode", opt::value<std::string>()->default_value("case"), "Run mode, can be case/coverage/filter")
        ("coverage.lcov_path", opt::value<std::string>()->default_value(""), "The lov binary path used to do coverage statistics")
        ("coverage.cov_paths", opt::value<std::string>()->default_value("*/src/dir1/*;*/src/dir2/*"))
        ("coverage.result_path", opt::value<std::string>()->default_value("./integration_test_result"), "The coverage result path")
        ("case.result_path", opt::value<std::string>()->default_value("./integration_test_result"), "The test result path")
        ("case.case_path", opt::value<std::string>()->default_value("./test_case/self_test_case.json"), "The test case file path")
        ("case.bin_path", opt::value<std::string>()->default_value("./"), "The binary file path, should contains planning, lam, car info and tmq_channel config files and all of the binaries")
        ("case.report_name", opt::value<std::string>()->default_value("report.htm"), "The test report name")
        ("case.filters", opt::value<std::string>()->default_value("all"), "The test filters, supported filters are: all,parallel,vertical,slant,obstacle,mod");
    
    opt::variables_map vm;
	opt::store(opt::parse_command_line(argc, argv, desc), vm);
    	if(vm.count("help")) {
		std::cout << desc << std::endl;
		return EXIT_FAILURE;
	}

    auto cfg_path = vm["config.path"].as<std::string>();

    // 读取配置文件中的配置信息
	try {
		opt::store(opt::parse_config_file<char>(cfg_path.data(), desc), vm);
	}catch(const opt::reading_file& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	try {
		// 填充值到vm中
		opt::notify(vm);
	}catch(const opt::required_option& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}


    std::cout << "Start to print parameters: \n";
    for(auto it=vm.begin(); it!=vm.end(); ++it) {
        std::cout << it->first << ": " << vm[it->first].as<std::string>() << std::endl;
    }
    return EXIT_SUCCESS;
}