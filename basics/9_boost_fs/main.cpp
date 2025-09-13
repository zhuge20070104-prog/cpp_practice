#include "boost/filesystem.hpp"
#include <iostream>
#include <sstream>
#include <regex>

struct  ImagePaths {
    std::string stitch_near_raw;
    std::string stitch_far;
};

ImagePaths getImagePaths(std::string const& case_file_path, std::string const& data_file_path) {
     boost::filesystem::path case_file_ {case_file_path};
    boost::filesystem::path rel_data_path {data_file_path};
    auto case_file_dir = case_file_.remove_leaf().remove_leaf();
    auto data_file_dir = rel_data_path.remove_leaf();

    std::string data_file_string = data_file_dir.string().substr(1);
    case_file_dir.concat(data_file_string);

    boost::filesystem::directory_iterator image_it(case_file_dir);
    boost::filesystem::path  stitched_near_raw;
    boost::filesystem::path  stitched_far;

    for(auto const& image_file: image_it) {
        if(image_file.path().string().find("stitched_near_raw") != std::string::npos) {
            stitched_near_raw = image_file.path();
        }
        if(image_file.path().string().find( "stitched_far") != std::string::npos) {
            stitched_far = image_file.path();
        }
    }

    return ImagePaths {stitched_near_raw.string(), stitched_far.string()};
}

int main(int argc, char* argv[]) {
    std::string case_file_path = "/home/fredric/code/verification/integrationcases/perception/test_case/perception_case_js.json";
    std::string data_file_path = "./test_case/case0/stitched_far.jpeg"; 
    for(int i=0; i<3; ++i) {
        auto image_paths = getImagePaths(case_file_path, data_file_path);

        std::cout <<  image_paths.stitch_near_raw << std::endl;
        std::cout << image_paths.stitch_far << std::endl;
    }

    // std::string src = "A B C .jpg";
    // auto res = std::regex_replace(src, std::regex(" "), ""); 
    // std::cout << res << std::endl;
    return EXIT_SUCCESS;
}