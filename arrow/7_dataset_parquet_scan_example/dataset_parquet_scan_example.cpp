#include <arrow/api.h>
#include <arrow/dataset/dataset.h>
#include <arrow/dataset/discovery.h>
#include <arrow/dataset/file_base.h>
#include <arrow/dataset/file_parquet.h>
#include <arrow/dataset/scanner.h>
#include <arrow/filesystem/filesystem.h>
#include <arrow/filesystem/path_util.h>
#include <arrow/compute/expression.h>
#include <parquet/arrow/writer.h>
#include <chrono>

#include <unistd.h>
#include <cstdlib>
#include <iostream>

using arrow::field;
using arrow::int16;
using arrow::Schema;
using arrow::Table;

namespace fs = arrow::fs;
namespace ds = arrow::dataset;
namespace cp = arrow::compute;

struct configuration {
    size_t repeat = 1;
    // Indicates if the Scanner::ToTable should consume in parallel.
    bool use_threads = true;
    std::vector<std::string> projected_columns {
        "pickup_at", "dropoff_at", "total_amount"
    };

    cp::Expression filter = cp::greater(cp::field_ref("total_amount"), cp::literal(100.0f));

    ds::InspectOptions inspect_options{};
    ds::FinishOptions finish_options{};
} conf;

arrow::Result<std::shared_ptr<arrow::Table>> CreateTable() {
    arrow::TimestampBuilder builder(arrow::timestamp(arrow::TimeUnit::NANO),
        arrow::default_memory_pool());
        
    int64_t time_base = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<int64_t> time_vector{time_base,
                                     time_base + 3000000000,
                                     time_base + 6000000000,
                                     time_base + 9000000000,
                                     time_base + 12000000000};

    ARROW_RETURN_NOT_OK(builder.AppendValues(time_vector));
    std::shared_ptr<arrow::Array> array_a;
    ARROW_RETURN_NOT_OK(builder.Finish(&array_a));
    std::cout << array_a->ToString() << std::endl;
    builder.Reset();

    time_base = time_base + 15000000000;
    std::vector<int64_t> time_vector1{time_base,
                                     time_base + 3000000000,
                                     time_base + 6000000000,
                                     time_base + 9000000000,
                                     time_base + 12000000000};

    ARROW_RETURN_NOT_OK(builder.AppendValues(time_vector1));
    std::shared_ptr<arrow::Array> array_b;
    ARROW_RETURN_NOT_OK(builder.Finish(&array_b));
    std::cout << array_b->ToString() << std::endl;
    

    arrow::FloatBuilder float_builder;
    std::vector<float> float_vector{100.0f, 200.0f, 300.0f, 90.0f, 400.0f};
    ARROW_RETURN_NOT_OK(float_builder.AppendValues(float_vector));
    std::shared_ptr<arrow::Array> array_c;
    ARROW_RETURN_NOT_OK(float_builder.Finish(&array_c));
    std::cout << array_c->ToString() << std::endl;

    auto schema = arrow::schema({arrow::field("pickup_at", arrow::timestamp(arrow::TimeUnit::NANO)),
                                 arrow::field("dropoff_at", arrow::timestamp(arrow::TimeUnit::NANO)),
                                 arrow::field("total_amount", arrow::float32())});
    auto table = arrow::Table::Make(schema, {array_a, array_b, array_c});
    
    return table;
} 


arrow::Result<std::string> CreateExampleParquetDataset(
    std::shared_ptr<fs::FileSystem> const& filesystem,
    std::string const& base_path 
) {
    ARROW_RETURN_NOT_OK(filesystem->CreateDir(base_path));
    ARROW_ASSIGN_OR_RAISE(auto table, CreateTable());
    ARROW_ASSIGN_OR_RAISE(auto output, filesystem->OpenOutputStream(base_path+"/data1.parquet"));
    ARROW_RETURN_NOT_OK(parquet::arrow::WriteTable(
        *table->Slice(0, 2), arrow::default_memory_pool(), output, 2048
    ));
    ARROW_ASSIGN_OR_RAISE(output, filesystem->OpenOutputStream(base_path+"/data2.parquet"));
    ARROW_RETURN_NOT_OK(parquet::arrow::WriteTable(
        *table->Slice(2), arrow::default_memory_pool(), output, 2048
    ));
    return base_path;
}

arrow::Result<std::shared_ptr<fs::FileSystem>> GetFileSystem() {
    std::shared_ptr<arrow::fs::FileSystem> setup_fs;
    char setup_path[256];
    char* result = getcwd(setup_path, 256);
    if(result == nullptr) {
        return arrow::Status::IOError("Fetching PWD failed.");
    }

    ARROW_ASSIGN_OR_RAISE(setup_fs, arrow::fs::FileSystemFromUriOrPath(setup_path));
    return setup_fs;
}

arrow::Result<std::shared_ptr<ds::Dataset>> GetDatasetFromDirectory(
    std::shared_ptr<fs::FileSystem> filesystem,
    std::shared_ptr<ds::ParquetFileFormat> format,
    std::string dir
) {
    fs::FileSelector s;
    s.base_dir = dir;
    s.recursive = true;

    ds::FileSystemFactoryOptions options;
    ARROW_ASSIGN_OR_RAISE(auto factory, ds::FileSystemDatasetFactory::Make(
        filesystem, s, format, options
    ));

    ARROW_ASSIGN_OR_RAISE(auto schema, factory->Inspect(conf.inspect_options));
    ARROW_ASSIGN_OR_RAISE(auto child, factory->Finish(conf.finish_options));
    ds::DatasetVector children {conf.repeat, child};
    auto dataset = ds::UnionDataset::Make(std::move(schema), std::move(children));
    return dataset;
}


arrow::Result<std::shared_ptr<ds::Scanner>> GetScannerFromDataset(
    std::shared_ptr<ds::Dataset> dataset, 
    std::vector<std::string> columns,
    cp::Expression filter,
    bool use_threads
) {
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, dataset->NewScan());
    if(!columns.empty()) {
        ARROW_RETURN_NOT_OK(scan_builder->Project(columns));
    }

    ARROW_RETURN_NOT_OK(scan_builder->Filter(filter));
    ARROW_RETURN_NOT_OK(scan_builder->UseThreads(use_threads));
    return scan_builder->Finish();
}

arrow::Result<std::shared_ptr<arrow::Table>> GetTableFromScanner(
    std::shared_ptr<ds::Scanner> scanner
) {
    return scanner->ToTable();
}




arrow::Status run_main() {
    ARROW_ASSIGN_OR_RAISE(auto filesystem, GetFileSystem());
    ARROW_ASSIGN_OR_RAISE(auto base_path, CreateExampleParquetDataset(filesystem, "parquet_dataset"));
    auto format = std::make_shared<ds::ParquetFileFormat>();
    ARROW_ASSIGN_OR_RAISE(auto dataset, GetDatasetFromDirectory(filesystem, format, base_path));
    ARROW_ASSIGN_OR_RAISE(auto scanner, GetScannerFromDataset(dataset, conf.projected_columns, 
        conf.filter, conf.use_threads));
    
    ARROW_ASSIGN_OR_RAISE(auto table, GetTableFromScanner(scanner));
    std::cout << "Table size: " << table->num_rows() << std::endl;
    std::cout << table->ToString() << std::endl;
    return arrow::Status::OK();
}

int main(int argc, char* argv[]) {
    arrow::Status st = run_main();
    if(!st.ok()) {
        std::cout << st << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

