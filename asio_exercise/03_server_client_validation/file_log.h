#ifndef _FREDRIC_FILE_LOG_H_
#define _FREDRIC_FILE_LOG_H_

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


struct file_log {
    std::fstream fs;
    std::string log_path;
    std::string log_file;

    // log文件的格式 {log_path}/log{index}.log
    file_log(std::string const& log_path_): log_path(log_path_) {
        int max_index = -1;
        for(auto& file: boost::filesystem::directory_iterator(log_path)) {
            auto file_name = file.path().filename().string();
            if(file_name.find(".log") != std::string::npos) {
                std::vector<std::string> result;
                boost::split(result, file_name, boost::is_any_of("."));
                std::string cur_index_s = boost::replace_all_copy(result[0], "log", "");
                int cur_index = std::atoi(cur_index_s.data());
                if(cur_index > max_index) {
                    max_index = cur_index;
                } 
            } 
        }
        max_index += 1;
        std::stringstream log_file_ss;
        log_file_ss << log_path << "/log"  << max_index << ".log";
        log_file = log_file_ss.str();
        std::cout << "current log file: " << log_file << "\n";
        fs.open(log_file, std::ios::out|std::ios::app);
        if(!fs.is_open()) {
            std::cerr << "open file failed\n";
        }
    }

    template <typename T>
    friend file_log& operator<<(file_log& log, T const& content) {
        log.fs << content;
        log.fs.flush();
        return log;
    }

    ~file_log() {
        fs.flush();
        fs.close();
    }
};


#endif