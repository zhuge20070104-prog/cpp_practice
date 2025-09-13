#include "gen_data.h"

int main(int argc, char* argv[]) {
    auto res = gen_data();
    if(res.status() != arrow::Status::OK()) {
        std::cerr << res.status() << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << res.ValueOrDie()->ToString() << std::endl;

    return EXIT_SUCCESS;
}