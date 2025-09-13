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


char kLeftRelationCsvData[] = R"csv(lkey,shared,ldistinct
1,4,7
2,5,8
11,20,21
3,6,9)csv";

char kRightRelationCsvData[] = R"csv(rkey,shared,rdistinct
1,10,13
124,10,11
2,11,14
3,12,15)csv";

arrow::Result<std::shared_ptr<ds::Dataset>> CreateDatasetFromCsvData(bool is_left) {
    arrow::io::IOContext const& io_context = arrow::io::default_io_context();
    std::shared_ptr<arrow::io::InputStream> input;
    std::string csv_data = is_left? kLeftRelationCsvData: kRightRelationCsvData;
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

arrow::Status DoHashJoin() {
    arrow::dataset::internal::Initialize();
    ARROW_ASSIGN_OR_RAISE(auto l_dataset, CreateDatasetFromCsvData(true));
    ARROW_ASSIGN_OR_RAISE(auto r_dataset, CreateDatasetFromCsvData(false));

    auto l_options = std::make_shared<arrow::dataset::ScanOptions>();
    l_options->projection = cp::project({}, {});

    // create empty projection: "default" projection where each field is mapped to a
    // field_ref
    auto r_options = std::make_shared<arrow::dataset::ScanOptions>();
    r_options->projection = cp::project({}, {});

    auto l_scan_node_options = arrow::dataset::ScanNodeOptions{l_dataset, l_options};
    auto r_scan_node_options = arrow::dataset::ScanNodeOptions{r_dataset, r_options};

    arrow::acero::Declaration left {"scan", std::move(l_scan_node_options)};
    arrow::acero::Declaration right {"scan", std::move(r_scan_node_options)};

    arrow::acero::HashJoinNodeOptions join_options {arrow::acero::JoinType::INNER,
        {"lkey"},
        {"rkey"},
        arrow::compute::literal(true),
        /*output suffix for l*/  "_l",  
        /*output suffix for r*/  "_r"};
    
    arrow::acero::Declaration hash_join {
        "hashjoin",
        {std::move(left), std::move(right)},
        join_options
    };

    ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::Table> response_table, 
        arrow::acero::DeclarationToTable(std::move(hash_join)));
    std::cout << "Results: " << response_table->ToString() << std::endl;
    return arrow::Status::OK();
}


int main(int argc, char* argv[]) {
    arrow::Status st = DoHashJoin();
    if(!st.ok()) {
        std::cerr << "Error occurred: " << st.message() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}



