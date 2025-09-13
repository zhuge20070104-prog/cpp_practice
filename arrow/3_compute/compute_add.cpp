#include "gen_data.h"

arrow::Status run_main() {
    // The Datum class is what all compute functions output to, and they can take Datums
    // as inputs, as well.
    auto table = gen_data().ValueOrDie();
    arrow::Datum sum;
    ARROW_ASSIGN_OR_RAISE(sum, arrow::compute::Sum({table->GetColumnByName("A")}));
    std::cout << "Datum kind: " << sum.ToString()
        << " Content type: " << sum.type()->ToString() << std::endl;
    
    std::cout << sum.scalar_as<arrow::Int64Scalar>().value << std::endl;

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