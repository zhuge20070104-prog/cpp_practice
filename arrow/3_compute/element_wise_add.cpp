#include "gen_data.h"


arrow::Status run_main() {
    auto res = gen_data();
    auto table = res.ValueOrDie();
    arrow::Datum element_wise_sum;

    ARROW_ASSIGN_OR_RAISE(element_wise_sum, arrow::compute::CallFunction(
        "add", {table->GetColumnByName("A"), table->GetColumnByName("B")}
    ));

    std::cout << "Datum kind: " << element_wise_sum.ToString() 
        << " Content type: " << element_wise_sum.type()->ToString() << std::endl;

    std::cout << element_wise_sum.chunked_array()->ToString() << std::endl;
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