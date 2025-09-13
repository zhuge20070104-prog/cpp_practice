#include "gen_data.h"

arrow::Status run_main() {  
    ARROW_RETURN_NOT_OK(PrepareEnv());
    return arrow::Status::OK();
}

int main(int argc, char * argv[]) {
    arrow::Status st = run_main();
    if(!st.ok()) {
        std::cerr << st << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
