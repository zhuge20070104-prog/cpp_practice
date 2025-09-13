#include <filesystem>
#include <vector>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include "pil.h"

namespace fs = std::filesystem;

struct train_test_split_t {
    train_test_split_t(std::string const& src_folder_, 
        std::string const& dst_folder_, float train_split_rate_):
        src_folder(src_folder_), dst_folder(dst_folder_),
        train_split_rate(train_split_rate_),
        pil_() {

    }

    
    void split() {
        auto class_paths = get_all_class_paths();
        make_dstinitation_dataset_dirs();
        for(auto & class_path: class_paths) {
            std::vector<fs::directory_entry> jpg_files;
            int count = count_files(class_path, &jpg_files);
            std::cout << "Finish count files, count: " << count << std::endl;
            if(count > 0) {
                int train_size = (int)(((float)count) * (train_split_rate));
                int test_size = count - train_size;
                std::string class_name = class_path.path().filename().string();
                std::string train_data_class_dir = train_data_dir + "/" + class_name;
                if(!fs::exists(train_data_class_dir)) {
                    fs::create_directories(train_data_class_dir);
                }
                
                std::string test_data_class_dir = test_data_dir + "/" + class_name;
                if(!fs::exists(test_data_class_dir)) {
                    fs::create_directories(test_data_class_dir);
                }
                for(int i=0; i<train_size; ++i) {
                    std::string dst_path = train_data_class_dir + "/" + jpg_files[i].path().filename().string();
                    fs::copy_file(jpg_files[i].path(), dst_path);
                }
                for(int i=train_size; i<jpg_files.size(); ++i) {
                    std::string dst_path = test_data_class_dir + "/" + jpg_files[i].path().filename().string();
                    fs::copy_file(jpg_files[i].path(), dst_path);
                }
            }
        }
    }

    int count_files(fs::path const& dir, std::vector<fs::directory_entry>* dir_files) {
        int count = 0;
        if (fs::exists(dir) && fs::is_directory(dir)) {
            for (auto& entry : fs::directory_iterator(dir)) {
                if (fs::is_regular_file(entry.path()) &&
                    entry.path().string().find(".jpg") != std::string::npos) {
                    bool success = pil_.open(entry.path().string());
                    if (!success) {
                        std::cerr << "Image [" << entry.path().string() << "] is not available, skipped!" << std::endl;
                        continue;
                    }
                    dir_files->push_back(entry);
                    ++count;
                } 
            }
        }
        return count;
    }

    void make_dstinitation_dataset_dirs() {
        std::stringstream train_folder_ss, test_folder_ss;
        train_folder_ss << dst_folder << "/train_dataset";
        test_folder_ss << dst_folder << "/test_dataset";
        
        std::cout << train_folder_ss.str() << std::endl;
        std::cout << test_folder_ss.str() << std::endl;

        if(fs::exists(train_folder_ss.str())) {
            fs::remove_all(train_folder_ss.str());
        }
        fs::create_directory(train_folder_ss.str());

        if(fs::exists(test_folder_ss.str())) {
            fs::remove_all(test_folder_ss.str());
        }
        fs::create_directory(test_folder_ss.str());
        train_data_dir = train_folder_ss.str();
        test_data_dir = test_folder_ss.str();
    }

    std::vector<fs::directory_entry> get_all_class_paths() {
        fs::path root_path(src_folder);
        std::vector<fs::directory_entry> results;
        if(fs::exists(root_path) && fs::is_directory(root_path)) {
            fs::directory_iterator dir_it(root_path);
            for(auto& entry: dir_it) {
                results.push_back(entry);
            }
        }
        return results;
    }


    std::string src_folder;
    std::string dst_folder;
    std::string train_data_dir;
    std::string test_data_dir;
    float train_split_rate;
    pil::pil_t pil_;
};

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cout << "Usage: ./bin/main {folder} {dst_folder} {train_split_rate}\n";
        std::cout << "Example: ./bin/main ./datasets ./results_ds 0.8\n";
        return EXIT_FAILURE;
    }

    std::string src_folder = std::string(argv[1]);
    std::string dst_folder = std::string(argv[2]);
    float train_split_rate = std::atof(argv[3]);
    train_test_split_t train_test_split(src_folder, dst_folder, train_split_rate);
    train_test_split.split();

    return EXIT_SUCCESS;
}