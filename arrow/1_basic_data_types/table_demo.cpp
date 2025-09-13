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

    arrow::Int16Builder int16_builder;
    int16_t years_raw[5] = {1990, 2000, 1995, 2000, 1995};
    ARROW_RETURN_NOT_OK(int16_builder.AppendValues(years_raw, 5));
    std::shared_ptr<arrow::Array> years;
    ARROW_ASSIGN_OR_RAISE(years, int16_builder.Finish());

    // 定义schema
    std::shared_ptr<arrow::Field> field_day, field_month, field_year;
    std::shared_ptr<arrow::Schema> schema;

    field_day = arrow::field("Day", arrow::int8());
    field_month = arrow::field("Month", arrow::int8());
    field_year = arrow::field("Year", arrow::int16());

    schema = arrow::schema({field_day, field_month, field_year});

    // 定义RecordBatch
    std::shared_ptr<arrow::RecordBatch> rbatch;
    rbatch = arrow::RecordBatch::Make(schema, days->length(), {days, months, years});
    std::cout << rbatch->ToString() << std::endl;

    int8_t days_raw2[5] = {6, 12, 3, 30, 22};
    ARROW_RETURN_NOT_OK(int8_builder.AppendValues(days_raw2, 5));
    std::shared_ptr<arrow::Array> days2;
    ARROW_ASSIGN_OR_RAISE(days2, int8_builder.Finish());

    int8_t months_raw2[5] = {5, 4, 11, 3, 2};
    ARROW_RETURN_NOT_OK(int8_builder.AppendValues(months_raw2, 5));
    std::shared_ptr<arrow::Array> months2;
    ARROW_ASSIGN_OR_RAISE(months2, int8_builder.Finish());

    int16_t years_raw2[5] = {1980, 2001, 1915, 2020, 1996};
    ARROW_RETURN_NOT_OK(int16_builder.AppendValues(years_raw2, 5));
    std::shared_ptr<arrow::Array> years2;
    ARROW_ASSIGN_OR_RAISE(years2, int16_builder.Finish());


    // 定义chunked array
    // ChunkedArrays let us have a list of arrays, which aren't contiguous
    // with each other. First, we get a vector of arrays.
    arrow::ArrayVector day_vecs {days, days2};
    std::shared_ptr<arrow::ChunkedArray> day_chunks = std::make_shared<arrow::ChunkedArray>(day_vecs);
    arrow::ArrayVector month_vecs {months, months2};
    std::shared_ptr<arrow::ChunkedArray> month_chunks = std::make_shared<arrow::ChunkedArray>(month_vecs);
    arrow::ArrayVector year_vecs {years, years2};
    std::shared_ptr<arrow::ChunkedArray> year_chunks = std::make_shared<arrow::ChunkedArray>(year_vecs);

    std::cout << "Print out table: " << std::endl;
    // 定义table
    std::shared_ptr<arrow::Table> table;
    table = arrow::Table::Make(schema, {day_chunks, month_chunks, year_chunks}, 10);
    std::cout << table->ToString() << std::endl;
    return arrow::Status::OK();
}

int main(int argc, char* argv[]) {
    auto st = run_main();
    if(!st.ok()) {
        std::cerr << st << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}