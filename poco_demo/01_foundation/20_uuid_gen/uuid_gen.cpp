#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Exception.h"
#include <iostream>

using Poco::UUID;
using Poco::UUIDGenerator;
using Poco::Exception;


enum ExitStatus {
    E_SUCCESS,
    E_UUID_EXCEPT
};

int main(int argc, char* argv[]) {
    UUID uuid;

    std::string arg;
    if(argc > 1) {
        arg = argv[1];
    }

    try {
        if(arg == "-random") {
            uuid = UUIDGenerator::defaultGenerator().createRandom();
        } else if(arg.empty()) {
            uuid = UUIDGenerator::defaultGenerator().create();
        } else {
            uuid = UUIDGenerator::defaultGenerator().createFromName(UUID::uri(), arg);
        }

        std::cout << uuid.toString() << std::endl;
    } catch(Exception const& ex) {
        std::cerr << ex.displayText() << std::endl;
        return E_UUID_EXCEPT;
    }
    return E_SUCCESS;
}