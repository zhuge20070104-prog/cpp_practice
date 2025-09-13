#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

struct ProcessUtil {
    static std::string subprocess_open(std::string const& cmd, std::string const& mode = "r") {
        std::stringstream res_ss;
        FILE *FileOpen;
        char line[300];                                 
        FileOpen = popen(cmd.c_str(), mode.c_str());                                                                            
        while(fgets(line, sizeof(line), FileOpen)){
            res_ss << line;
        }
        pclose(FileOpen);
        return res_ss.str();
    }

    static bool check_process_started(std::string const& process_name) {
        std::stringstream process_check_ss;
        process_check_ss << "ps -a | grep " << process_name;
        auto process_str = subprocess_open(process_check_ss.str());
        if(process_str.find(process_name) != std::string::npos) {
            return true;
        } else {
            return false;
        }
    }
};


int main(int argc, char* argv[]) {
    auto spm_res = ProcessUtil::check_process_started("lam");
   
    if(spm_res) {
        std::cout << "Process lam started ..." << std::endl;
    } else {
        std::cout << "Process lam not started ..." << std::endl;
    }
    return EXIT_SUCCESS;
}