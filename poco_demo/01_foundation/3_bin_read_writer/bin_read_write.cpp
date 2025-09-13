#include "Poco/BinaryWriter.h"
#include "Poco/BinaryReader.h"

#include <fstream>
#include <iostream>
#include <sstream>


using Poco::BinaryReader;
using Poco::BinaryWriter;


void write_binary_stream_to_file_directly() {
    std::fstream fs("./ele_d.b", std::ios::out | std::ios::binary);
    BinaryWriter writer(fs);
    writer << true // bool
        << 'x'     // char
        << 42      // int
        << 3.14159265  // double
        << "foo bar";  // std::string
    fs.flush();
    fs.close();
}

void read_binary_stream_from_file_directly() {
    std::fstream ifs("./ele_d.b", std::ios::in | std::ios::binary);
    BinaryReader reader(ifs);
    bool b;
    char c;
    int i;
    double d;
    std::string s;
    reader >> b
           >> c
           >> i 
           >> d 
           >> s;

    std::cout << b << std::endl
              << c << std::endl
              << i << std::endl
              << d << std::endl 
              << s << std::endl; 

    ifs.close();
}

void write_and_read_binary_stream_str_stream() {
    std::stringstream str;
    BinaryWriter writer(str);
    writer << true 
           << 'x'
           << 42
           << 3.14159265
           << "foo bar";
    
    bool b;
    char c;
    int i;
    double d;
    std::string s;

    BinaryReader reader(str);
    reader >> b 
           >> c
           >> i 
           >> d 
           >> s;

    std::cout << b << std::endl
              << c << std::endl
              << i << std::endl
              << d << std::endl
              << s << std::endl;
}

int main(int argc, char* argv[]) {
    write_binary_stream_to_file_directly();
    read_binary_stream_from_file_directly();

    write_and_read_binary_stream_str_stream();
    return EXIT_SUCCESS;
}