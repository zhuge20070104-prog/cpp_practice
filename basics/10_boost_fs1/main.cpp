#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>
#include <string>

struct Directory {
    std::string parent_directory;
    std::string second_directory;
    std::string case_name;
};

std::vector<std::string> str_split(std::string const& input, std::string const& regex) {
    std::regex re(regex);
    std::sregex_token_iterator
        first{input.begin(), input.end(), re, -1},
        last;
    return {first, last};
}

void get_file_parent_paths(boost::filesystem::path const& path_, std::vector<std::string>& result_paths, std::vector<std::string> const& end_dirs) {
    boost::filesystem::directory_iterator dir_it{path_};
    for(auto const& end_dir: end_dirs) {
        if(path_.string().find(end_dir)!=std::string::npos) {
            result_paths.push_back(path_.string());
            return;
        } 
    }
    for(auto& entry: dir_it) { 
        get_file_parent_paths(entry.path(), result_paths, end_dirs);      
    }
}

std::vector<std::string> get_file_second_paths(boost::filesystem::path const& path_)  {
    std::vector<std::string> results_snd;
    boost::filesystem::directory_iterator dir_it{path_};
    for(auto const& entry: dir_it) {
        results_snd.push_back(entry.path().filename().string());
    }
    return results_snd;
}

int main(int argc, char* argv[]) {
    
    boost::filesystem::path root_p {"/home/fredric/data1"};
    std::vector<std::string> parent_paths;
    get_file_parent_paths(root_p, parent_paths, {"SurroundViewCameraFrames", "StitchedImage"});

    std::vector<Directory> directories;
    std::string topic_name {"StitchedImage"};
    for(auto  parent_path: parent_paths) {
        if(parent_path.find(topic_name) != std::string::npos) {
            auto snd_paths = get_file_second_paths(parent_path);
            // Warning: 此处注意后面那个"/" 是必须的
            boost::replace_all(parent_path, "/home/fredric/data1/", "");
            std::vector<std::string> path_infos;
            boost::split(path_infos, parent_path, boost::is_any_of("/"));
            std::string car_type = path_infos[0];
            std::string ps_type = path_infos[1];
            std::string place = path_infos[2];
            std::string date = path_infos[3];
            std::string topic = path_infos[4];
            int i {0};
            for(auto const& snd_path: snd_paths) {
                std::stringstream case_name_ss;
                case_name_ss << date << "_" << topic << "_" << place << "_" << car_type << "_"  << ps_type;
                case_name_ss << "_Angle_" << i;
                directories.push_back(Directory{parent_path, snd_path, case_name_ss.str()});
                ++i;
            }
        }
    }


    for(auto const& dir: directories) {
        std::cout << dir.parent_directory << " | " << dir.second_directory << " | " << dir.case_name << std::endl;  
    }
    return EXIT_SUCCESS;
}