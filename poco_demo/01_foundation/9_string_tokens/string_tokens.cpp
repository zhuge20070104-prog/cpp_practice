#include "Poco/StringTokenizer.h"

#include <iostream>

using Poco::StringTokenizer;

int main(int argc, char* argv[]) {
    std::string tokens = "white; black; magenta, blue, green; yellow";
    StringTokenizer tokenizer(tokens, ";,", StringTokenizer::TOK_TRIM);

    for(StringTokenizer::Iterator it=tokenizer.begin(); it!=tokenizer.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return EXIT_SUCCESS;
}