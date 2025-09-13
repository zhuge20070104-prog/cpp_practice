#include "gen_data.h"

arrow::Status run_main() {
    auto res = gen_data();
    auto table = res.ValueOrDie();

    arrow::Datum third_item;    
    arrow::compute::IndexOptions index_options;
    index_options.value = arrow::MakeScalar(2223);
    ARROW_ASSIGN_OR_RAISE(third_item, 
        arrow::compute::CallFunction(
            "index", {table->GetColumnByName("A")}, &index_options
        ));
    
    std::cout << "Datum kind: " << third_item.ToString()
        << " Content type: " << third_item.type()->ToString() 
        << std::endl;
    
    std::cout << third_item.scalar_as<arrow::Int64Scalar>().value << std::endl;
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