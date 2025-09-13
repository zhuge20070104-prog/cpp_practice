#include <iostream>
#include <arrow/api.h>

arrow::Status run_main() {
    arrow::Int16Builder int16_builder;
    int16_t years_raw[5] = {1990, 2000, 1995, 2000, 1995};
    ARROW_RETURN_NOT_OK(int16_builder.AppendValues(years_raw, 5));
    std::shared_ptr<arrow::Array> years;
    ARROW_ASSIGN_OR_RAISE(years, int16_builder.Finish());

    std::cout << "Print out int16 Array: " << std::endl;
    auto years_int16 = std::static_pointer_cast<arrow::Int16Array>(years);
    for(int i=0; i<years_int16->length(); ++i) {
        std::cout << (int)years_int16->Value(i) << std::endl;
    }
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