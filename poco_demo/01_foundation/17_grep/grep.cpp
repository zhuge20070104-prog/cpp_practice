#include "Poco/RegularExpression.h"
#include <iostream>

using Poco::RegularExpression;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << ":[-i] [-x] pattern" << std::endl;
        return EXIT_FAILURE;
    }

    std::string pattern;

    int options;
    for(int i=1; i<argc; ++i) {
        std::string arg(argv[i]);
        if(arg == "-i") {
            // 不区分大小写
            options += RegularExpression::RE_CASELESS;
        } else if(arg == "-x") {
            options += RegularExpression::RE_EXTENDED;
        } else {
            pattern = arg;
        }
    }


    RegularExpression re(pattern, options);
    int c = std::cin.get();
    // -1表示EOF结束符
    // 可以按Ctrl + C结束
    // 默认不带options的构造函数，最好使
    while(c != -1) {
        std::string line;
        while(c != -1 && c != '\n') {
            line += (char) c;
            c = std::cin.get();
        }

        RegularExpression::Match match;
        if(re.match(line, match)) {
            std::cout << line << std::endl;
        }

        if(c != -1) c = std::cin.get();
    } 
    return EXIT_SUCCESS;
}