#include <iostream>
#include <arrow/api.h>

arrow::Status run_main() {
    arrow::Int8Builder int8_builder;
    int8_t days_raw[5] = {1, 12, 17, 23, 28};
    ARROW_RETURN_NOT_OK(int8_builder.AppendValues(days_raw, 5));
    std::shared_ptr<arrow::Array> days;
    ARROW_ASSIGN_OR_RAISE(days, int8_builder.Finish());

    int8_t months_raw[5] = {1, 3, 5, 7, 1};
    ARROW_RETURN_NOT_OK(int8_builder.AppendValues(months_raw, 5));
    std::shared_ptr<arrow::Array> months;
    ARROW_ASSIGN_OR_RAISE(months, int8_builder.Finish());

    std::cout << "Print days data: " << std::endl;
    auto days_int8 = std::static_pointer_cast<arrow::Int8Array>(days);
    for(int i=0; i<days_int8->length(); ++i) {
        std::cout << (int)days_int8->Value(i) << std::endl;
    }

    std::cout << "Print month data: " << std::endl;
    auto months_int8 = std::static_pointer_cast<arrow::Int8Array>(months);
    for(int i=0; i<months_int8->length(); ++i) {
        std::cout << (int)months_int8->Value(i) << std::endl;
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
