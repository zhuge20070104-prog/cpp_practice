#include "Poco/InflatingStream.h"
#include "Poco/StreamCopier.h"

#include <iostream>
#include <fstream>

using Poco::InflatingInputStream;
using Poco::StreamCopier;

enum ErrorCode {
    ERR_ARG_COUNT=1,
    ERR_OPEN_INPUT,
    ERR_OPEN_OUTPUT,
    ERR_WRITE_OUTPUT
};

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << ": <intput_file> <output_file>" << std::endl
            << " read deflated(compressed) <input_file>, inflate it and write the result to <output_file>"
            << std::endl;
        return ERR_ARG_COUNT;
    }


    std::ifstream istr(argv[1], std::ios::binary);
    if(!istr) {
        std::cerr << "Cannot open input file: " << argv[1] << std::endl;
        return ERR_OPEN_INPUT;
    }

    std::ofstream ostr(argv[2], std::ios::binary);
    if(!ostr) {
        std::cerr << "Cannot open output file: " << argv[2] << std::endl;
        return ERR_OPEN_OUTPUT;
    }

    InflatingInputStream inflator(istr);
    StreamCopier::copyStream(inflator, ostr);

    if(!ostr) {
        std::cerr << "Error writing output file: " << argv[2] << std::endl;
        return ERR_WRITE_OUTPUT;
    }

    return EXIT_SUCCESS;
}