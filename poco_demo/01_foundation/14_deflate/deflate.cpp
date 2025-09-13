// Compress a file
#include "Poco/DeflatingStream.h"
#include "Poco/StreamCopier.h"

#include <iostream>
#include <fstream>

using Poco::DeflatingOutputStream;
using Poco::StreamCopier;

enum ErrCode {
    E_PARAM_COUNT,
    E_OPEN_INPUT_FILE,
    E_OPEN_OUTPUT_FILE,
    E_WRITE_OUTPUT_FILE
};


int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << ": <input_file> <output_file>" << std::endl
            << "Read <input_file>, deflate (compress) it and write the result to <output_file>" 
            << std::endl;
        return E_PARAM_COUNT;
    }

    std::ifstream istr(argv[1], std::ios::binary);
    if(!istr) {
        std::cout << "Cannot open input file: " << argv[1] << std::endl;
        return E_OPEN_INPUT_FILE;
    }

    std::ofstream ostr(argv[2], std::ios::binary);
    if(!ostr) {
        std::cout << "Cannot open output file: " << argv[2] << std::endl;
        return E_OPEN_OUTPUT_FILE;
    }

    DeflatingOutputStream deflater(ostr);
    StreamCopier::copyStream(istr, deflater);
    if(!ostr) {
        std::cerr << "Error writting output file: " << argv[2] << std::endl;
        return E_WRITE_OUTPUT_FILE;
    }

    return EXIT_SUCCESS;
}