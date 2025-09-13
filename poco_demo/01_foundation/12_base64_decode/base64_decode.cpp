#include "Poco/Base64Decoder.h"
#include "Poco/StreamCopier.h"

#include <fstream>
#include <iostream>


using Poco::Base64Decoder;
using Poco::StreamCopier;


enum FailureCode {
    LESS_ARG=1,
    OPEN_IN_FILE_FAIL,
    OPEN_OUT_FILE_FAIL,
    WRITE_OUT_FAIL
};

int main(int argc, char* argv[]) {

    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << ": <input_file> <output_file>" << std::endl
            << "  read base64-encoded <input_file>, decode it and write the result to <output_file>" << std::endl;
        return LESS_ARG;
    }

    std::ifstream istr(argv[1]);
    if(!istr) {
        std::cerr << "Can not open input file: " << argv[1] << std::endl;
        return OPEN_IN_FILE_FAIL;
    }

    std::ofstream ostr(argv[2], std::ios::binary);
    if(!ostr) {
        std::cerr << "Can not open output file: " << argv[2] << std::endl;
        return OPEN_OUT_FILE_FAIL;
    }

    Base64Decoder decoder(istr);
    StreamCopier::copyStream64(decoder, ostr);

    if(!ostr) {
        std::cerr << "Error writing output file: " << argv[2] << std::endl;
        return WRITE_OUT_FAIL;
    }

    return EXIT_SUCCESS;
}