#include "file_gen.h"
#include <iostream>

arrow::Status run_main() {
    ARROW_RETURN_NOT_OK(gen_initial_file());
    return arrow::Status::OK();
}

int main(int argc, char* argv[]) {
    arrow::Status st = run_main();
    if(!st.ok()) {
        std::cerr << st << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}