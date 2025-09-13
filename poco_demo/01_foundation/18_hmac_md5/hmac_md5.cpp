#include "Poco/HMACEngine.h"
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/StreamCopier.h"
#include <fstream>
#include <iostream>

using Poco::DigestEngine;
using Poco::HMACEngine;
using Poco::MD5Engine;
using Poco::DigestOutputStream;
using Poco::StreamCopier;


enum EXITStatus {
    E_SUCCESS,
    E_PARAM,
    E_OPENFILE
};

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << argv[0] << ": <passphrase> <input_file>" << std::endl
            << " create the HMAC-MD5 for <inputfile>, using <passphrase>" << std::endl;
        
        return E_PARAM;
    }

    std::string passphrase(argv[1]);
    std::ifstream istr(argv[2], std::ios::binary);
    if(!istr) {
        std::cerr << "Can not open input file: " << argv[2] << std::endl;
        return E_OPENFILE;
    }

    HMACEngine<MD5Engine> hmac(passphrase);
    DigestOutputStream dos(hmac);

    StreamCopier::copyStream(istr, dos);
    dos.close();

    std::cout << DigestEngine::digestToHex(hmac.digest()) << std::endl;
    
    return E_SUCCESS;
}