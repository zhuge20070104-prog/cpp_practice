#include "gen_data.h"

arrow::Result<std::shared_ptr<arrow::Table>> gen_data() {
    arrow::Int32Builder int32_builder;
    int32_t some_nums_raw[5] = {34, 624, 2223, 5654, 4356};
    ARROW_RETURN_NOT_OK(int32_builder.AppendValues(some_nums_raw, 5));
    std::shared_ptr<arrow::Array> some_nums;
    ARROW_ASSIGN_OR_RAISE(some_nums, int32_builder.Finish());

    int32_t more_nums_raw[5] = {75342, 23, 64, 17, 736};
    ARROW_RETURN_NOT_OK(int32_builder.AppendValues(more_nums_raw, 5));
    std::shared_ptr<arrow::Array> more_nums;
    ARROW_ASSIGN_OR_RAISE(more_nums, int32_builder.Finish());

    std::shared_ptr<arrow::Field> field_a, field_b;
    std::shared_ptr<arrow::Schema> schema;

    field_a = arrow::field("A", arrow::int32());
    field_b = arrow::field("B", arrow::int32());
    
    schema = arrow::schema({field_a, field_b});

    std::shared_ptr<arrow::Table> table;
    table = arrow::Table::Make(schema, {some_nums, more_nums}, 5);
    return arrow::ToResult(table);
}   