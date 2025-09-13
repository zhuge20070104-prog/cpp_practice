#include "Poco/DirectoryIterator.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"

#include <iostream>

using Poco::DirectoryIterator;
using Poco::File;
using Poco::Path;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;


int main(int argc, char* argv[])  {
    std::string dir;
    if(argc > 1) {
        dir = argv[1];
    } else {
        dir = Path::current();
    }

    try {
        DirectoryIterator it(dir);
        DirectoryIterator end;
        while(it != end) {
            Path p(it->path());
            std::cout << (it->isDirectory()? 'd': '-')
                      << (it->canRead()? 'r': '-')
                      << (it->canWrite()? 'w': '-')
                      << ' '
                      << DateTimeFormatter::format(it->getLastModified(), DateTimeFormat::SORTABLE_FORMAT)
                      << ' '
                      << p.getFileName()
                      << std::endl; 
            ++it;
        }
    }catch(Poco::Exception const& ex) {
        std::cerr << ex.displayText() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}