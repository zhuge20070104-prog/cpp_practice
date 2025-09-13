#include "Poco/Base64Encoder.h"
#include "Poco/StreamCopier.h"
#include <iostream>
#include <fstream>

using Poco::Base64Encoder;
using Poco::StreamCopier;


enum ErrorCode {
    PARAM_COUNT_ERR=1,
    INPUT_FILE_OPEN_ERR,
    OUT_FILE_OPEN_ERR,
    WRITE_OUT_ERR
};

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << ": <input_file> <output_file>" << std::endl
            << "  read <input_file>, base64-encode it and write the result to <output_file>"
            << std::endl;
            return PARAM_COUNT_ERR;
    }

    std::ifstream istr(argv[1], std::ios::binary);
    if(!istr) {
        std::cerr << "Cannot open input file: " << argv[1] << std::endl;
        return INPUT_FILE_OPEN_ERR;
    }

    std::ofstream ostr(argv[2]);
    if(!ostr) {
        std::cerr << "Cannot open output file: " << argv[2] << std::endl;
        return OUT_FILE_OPEN_ERR;
    }

    Base64Encoder encoder(ostr);
    StreamCopier::copyStream(istr, encoder);

    if(!ostr) {
        std::cerr << "Error writing output file: " << argv[2] << std::endl;
        return WRITE_OUT_ERR;
    }
    
    return EXIT_SUCCESS;
}