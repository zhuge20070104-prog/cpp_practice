#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>

void Write(std::string const& file_name) {
    std::fstream fs(file_name, std::ios::out);
    if(!fs.is_open()) {
        std::cout << "Open file: " << file_name << " for write failed.." << std::endl;
        return;  
    }

    fs << "Hello world\n";
    fs.flush();
    fs.close();
}

void Read(std::string const& file_name) {
    std::fstream fs(file_name, std::ios::in);
    if(!fs.is_open()) {
        std::cout << "Open file: " << file_name << " for read failed.." << std::endl;
        return;  
    } 
    std::stringstream ss;
    ss << fs.rdbuf();
    std::cout << ss.str();
    fs.close();
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    std::string hello_file = "../hello.txt";
    Write(hello_file);
    Read(hello_file);
    app.exec();
}