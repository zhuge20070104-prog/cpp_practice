#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/StreamCopier.h"
#include <fstream>
#include <iostream>


using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::DigestOutputStream;
using Poco::StreamCopier;

enum ExitStatus {
    E_SUCCESS,
    E_PARAM,
    E_OPEN_FILE
};

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "usage: " << argv[0] << ": <intput_file>" << std::endl
            << "  create the MD5 digest for <input_file>" << std::endl;
        return E_PARAM;
    }

    std::ifstream istr(argv[1], std::ios::binary);
    if(!istr) {
        std::cerr << "Can not open input file: " << argv[1] << std::endl;
        return E_OPEN_FILE;
    }

    MD5Engine md5;
    DigestOutputStream dos(md5);
    StreamCopier::copyStream(istr, dos);
    dos.close();

    std::cout << DigestEngine::digestToHex(md5.digest()) << std::endl;
    return E_SUCCESS;
}