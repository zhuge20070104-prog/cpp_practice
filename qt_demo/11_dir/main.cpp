#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <string>
#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    std::string path = "../conanfile.txt";
    auto conan_file_exists = fs::exists(path);
    if(conan_file_exists) {
        std::cout << "Conan file: " << path << " exists" << std::endl;
    } else {
        std::cout << "Conan file: " << path << " doesn't exists" << std::endl;
    }

    fs::path root_drive("/");
    std::cout << "Print all drives under root drive...." << std::endl;
    for(auto const& sub_drive: fs::directory_iterator(root_drive)) {
        if(fs::is_directory(sub_drive)) {
            std::cout << sub_drive.path().string() << std::endl;
        }
    }

    fs::path proj_dir("../");
    std::cout << "Print all files under current project directory..." << std::endl;
    for(auto const& sub_dir: fs::directory_iterator(proj_dir)) {
        if(fs::is_directory(sub_dir)) {
            std::cout << "Directory: " << sub_dir.path().string() << std::endl; 
        }

        if(fs::is_regular_file(sub_dir)) {
            std::cout << "File: " << sub_dir.path().string() << std::endl;
        }
    }
    app.exec();
}