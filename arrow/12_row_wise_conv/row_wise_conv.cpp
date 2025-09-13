#include <arrow/api.h>
#include <arrow/result.h>

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

using arrow::DoubleBuilder;
using arrow::Int64Builder;
using arrow::ListBuilder;


struct data_row {
    int64_t id;
    int64_t components;
    std::vector<double> component_cost;
};

arrow::Result<std::shared_ptr<arrow::Table>> VectorToColumnarTable(
    std::vector<data_row> const& rows
) {
    arrow::MemoryPool* pool = arrow::default_memory_pool();
    Int64Builder id_builder(pool);
    Int64Builder components_builder(pool);
    ListBuilder component_cost_builder(pool, std::make_shared<DoubleBuilder>(pool));
    // 下面的builder被component_cost_builder拥有
    DoubleBuilder* component_item_cost_builder = 
        (static_cast<DoubleBuilder*>(component_cost_builder.value_builder()));
    
    for(data_row const& row: rows) {
        ARROW_RETURN_NOT_OK(id_builder.Append(row.id));
        ARROW_RETURN_NOT_OK(components_builder.Append(row.components));
        
        // Indicate the start of a new list row. This will memorise the current
        // offset in the values builder.
        ARROW_RETURN_NOT_OK(component_cost_builder.Append());
        ARROW_RETURN_NOT_OK(component_item_cost_builder->AppendValues(row.component_cost.data(), 
            row.component_cost.size()));
    }

    std::shared_ptr<arrow::Array> id_array;
    ARROW_RETURN_NOT_OK(id_builder.Finish(&id_array));
    
    std::shared_ptr<arrow::Array> components_array;
    ARROW_RETURN_NOT_OK(components_builder.Finish(&components_array));

    // No need to invoke component_item_cost_builder.Finish because it is implied by
    // the parent builder's Finish invocation.
    std::shared_ptr<arrow::Array> component_cost_array;
    ARROW_RETURN_NOT_OK(component_cost_builder.Finish(&component_cost_array));

    std::vector<std::shared_ptr<arrow::Field>> schema_vector = {
        arrow::field("id", arrow::int64()),
        arrow::field("components", arrow::int64()),
        arrow::field("component_cost", arrow::list(arrow::float64()))
    };

    auto schema = std::make_shared<arrow::Schema>(schema_vector);

    std::shared_ptr<arrow::Table> table = arrow::Table::Make(schema,
        {id_array, components_array, component_cost_array});

    return table;
}


arrow::Result<std::vector<data_row>> ColumnarTableToVector(
    std::shared_ptr<arrow::Table> const& table
) {
    std::vector<std::shared_ptr<arrow::Field>> schema_vector = {
        arrow::field("id", arrow::int64()),
        arrow::field("components", arrow::int64()),
        arrow::field("component_cost", arrow::list(arrow::float64()))
    };

    auto expected_schema = std::make_shared<arrow::Schema>(schema_vector);
    if(!expected_schema->Equals(*table->schema())) {
        return arrow::Status::Invalid("Schemas are not matching!");
    }

    auto ids = std::static_pointer_cast<arrow::Int64Array>(table->column(0)->chunk(0));
    auto components = std::static_pointer_cast<arrow::Int64Array>(table->column(1)->chunk(0));
    auto component_cost = std::static_pointer_cast<arrow::ListArray>(table->column(2)->chunk(0));
    auto component_cost_values = std::static_pointer_cast<arrow::DoubleArray>(component_cost->values());
    double const* ccv_ptr = component_cost_values->raw_values();

    std::vector<data_row> rows;
    for(int64_t i=0; i<table->num_rows(); ++i) {
        int64_t id = ids->Value(i);
        int64_t component = components->Value(i);
        double const* first = ccv_ptr + component_cost->value_offset(i);
        double const* last = ccv_ptr + component_cost->value_offset(i+1);
        std::vector<double> components_vec(first, last);
        rows.push_back({id, component, components_vec}); 
    }

    return rows;
}

arrow::Status RunRowConversion() {
    std::vector<data_row> original_rows = {
      {1, 1, {10.0}}, {2, 3, {11.0, 12.0, 13.0}}, {3, 2, {15.0, 25.0}}};
    
    std::shared_ptr<arrow::Table> table;
    std::vector<data_row> converted_rows;

    ARROW_ASSIGN_OR_RAISE(table, VectorToColumnarTable(original_rows));

    ARROW_ASSIGN_OR_RAISE(converted_rows, ColumnarTableToVector(table));

    assert(original_rows.size() == converted_rows.size());

    // Print out contents of table, should get
    // ID Components Component prices
    // 1  1          10
    // 2  3          11  12  13
    // 3  2          15  25
    std::cout << std::left << std::setw(3) << "ID " << std::left << std::setw(11)
                << "Components " << std::left << std::setw(15) << "Component prices "
                << std::endl;
    for (const auto& row : converted_rows) {
        std::cout << std::left << std::setw(3) << row.id << std::left << std::setw(11)
                << row.components;
        for (const auto& cost : row.component_cost) {
        std::cout << std::left << std::setw(4) << cost;
        }
        std::cout << std::endl;
    }
    return arrow::Status::OK();
}

int main(int argc, char* argv[]) {
    arrow::Status st = RunRowConversion();
    if(!st.ok()) {
        std::cerr << st.ToString() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}