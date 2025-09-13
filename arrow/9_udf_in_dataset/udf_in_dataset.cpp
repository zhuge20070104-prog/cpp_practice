#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <arrow/csv/api.h>
#include "arrow/acero/exec_plan.h"
#include "arrow/compute/expression.h"

#include <arrow/dataset/dataset.h>
#include <arrow/dataset/plan.h>
#include <arrow/dataset/scanner.h>

#include <arrow/io/interfaces.h>
#include <arrow/io/memory.h>
#include <arrow/io/stdio.h>

#include <arrow/filesystem/filesystem.h>

#include <arrow/result.h>
#include <arrow/status.h>

#include <arrow/util/vector.h>

#include <iostream>
#include <vector>


namespace ds = arrow::dataset;
namespace cp = arrow::compute;


char ch_csv_data[] = R"csv(k1,k2,k3
1,4,7
2,5,8
11,20,21
3,6,9)csv";

cp::FunctionDoc func_doc{
    "User-defined-function usage to demonstrate registering an out-of-tree function",
    "returns x + y + z",
    {"x", "y", "z"},
    "UDFOptions"
};

arrow::Result<std::shared_ptr<ds::Dataset>> CreateDatasetFromCsvData() {
    arrow::io::IOContext const& io_context = arrow::io::default_io_context();
    std::shared_ptr<arrow::io::InputStream> input;
    std::string csv_data = ch_csv_data;
    std::cout << csv_data << std::endl;

    std::string_view sv = csv_data;
    input = arrow::io::BufferReader::FromString(std::string(sv));
    auto read_options = arrow::csv::ReadOptions::Defaults();
    auto parse_options = arrow::csv::ParseOptions::Defaults();
    auto convert_options = arrow::csv::ConvertOptions::Defaults();

    ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::csv::TableReader> table_reader,
        arrow::csv::TableReader::Make(io_context, input,
            read_options, parse_options, convert_options)); 
    ARROW_ASSIGN_OR_RAISE(auto maybe_table, table_reader->Read());
    auto ds_ = std::make_shared<ds::InMemoryDataset>(maybe_table);
    arrow::Result<std::shared_ptr<ds::InMemoryDataset>> result(std::move(ds_));
    return result;
}

arrow::Status SampleFunction(cp::KernelContext* ctx, cp::ExecSpan const& batch,
    cp::ExecResult* out) {
    
    // return x + y + z
    const int64_t* x = batch[0].array.GetValues<int64_t>(1);
    const int64_t* y = batch[1].array.GetValues<int64_t>(1);
    const int64_t* z = batch[2].array.GetValues<int64_t>(1);
    int64_t* out_values = out->array_span_mutable()->GetValues<int64_t>(1);
    for (int64_t i = 0; i < batch.length; ++i) {
        *out_values++ = *x++ + *y++ + *z++;
    }
    return arrow::Status::OK();
}

arrow::Status UDFDatasetScan() {
    ARROW_ASSIGN_OR_RAISE(auto data_set, CreateDatasetFromCsvData());
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, data_set->NewScan());

    // Customized add three function
    std::string const name = "add_three";
    auto func = std::make_shared<cp::ScalarFunction>(name, cp::Arity::Ternary(), func_doc);
    cp::ScalarKernel kernel({arrow::int64(), arrow::int64(), arrow::int64()},
        arrow::int64(), SampleFunction);

    kernel.mem_allocation = cp::MemAllocation::PREALLOCATE;
    kernel.null_handling = cp::NullHandling::INTERSECTION;
    ARROW_RETURN_NOT_OK(func->AddKernel(std::move(kernel)));

    auto registry = cp::GetFunctionRegistry();
    ARROW_RETURN_NOT_OK(registry->AddFunction(std::move(func)));

    // Start to project the result dataset
    ARROW_RETURN_NOT_OK(scan_builder->Project({
        cp::field_ref("k1"),
        cp::field_ref("k2"),
        cp::field_ref("k3"),
        cp::call("add_three", {cp::field_ref("k1"), cp::field_ref("k2"), cp::field_ref("k3")})
    }, {"k1", "k2", "k3", "sum"}));

    ARROW_ASSIGN_OR_RAISE(auto scanner, scan_builder->Finish());
    ARROW_ASSIGN_OR_RAISE(auto table, scanner->ToTable());
    std::cout << "Result " << table->num_rows() << " rows" << std::endl;
    std::cout << table->ToString() << std::endl;
    return arrow::Status::OK();
} 


int main(int argc, char* argv[]) {
    arrow::Status st = UDFDatasetScan();
    if(!st.ok()) {
        std::cerr << "Error occurred: " << st.message() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}



