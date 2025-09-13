#include <arrow/api.h>
#include <arrow/dataset/api.h>
// We use Parquet headers for setting up examples; they are not required for using
// datasets.
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>

#include <unistd.h>
#include <iostream>

arrow::Result<std::shared_ptr<arrow::Table>> CreateTable() {
    auto schema = arrow::schema({arrow::field("a", arrow::int64()), 
        arrow::field("b", arrow::int64()),
        arrow::field("c", arrow::int64())});
    std::shared_ptr<arrow::Array> array_a;
    std::shared_ptr<arrow::Array> array_b;
    std::shared_ptr<arrow::Array> array_c;

    arrow::NumericBuilder<arrow::Int64Type> builder;
    ARROW_RETURN_NOT_OK(builder.AppendValues({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    ARROW_RETURN_NOT_OK(builder.Finish(&array_a));
    builder.Reset();

    ARROW_RETURN_NOT_OK(builder.AppendValues({9, 8, 7, 6, 5, 4, 3, 2, 1, 0}));
    ARROW_RETURN_NOT_OK(builder.Finish(&array_b));
    builder.Reset();
    ARROW_RETURN_NOT_OK(builder.AppendValues({1, 2, 1, 2, 1, 2, 1, 2, 1, 2}));
    ARROW_RETURN_NOT_OK(builder.Finish(&array_c));

    return arrow::Table::Make(schema, {array_a, array_b, array_c});
}

arrow::Result<std::string> CreateExampleParquetDataset(
    std::shared_ptr<arrow::fs::FileSystem> const& filesystem,
    std::string const& root_path
) {
    auto base_path = root_path + "parquet_dataset";
    ARROW_RETURN_NOT_OK(filesystem->CreateDir(base_path));
    ARROW_ASSIGN_OR_RAISE(auto table, CreateTable());
    ARROW_ASSIGN_OR_RAISE(auto output, filesystem->OpenOutputStream(base_path + "/data1.parquet"));
    ARROW_RETURN_NOT_OK(parquet::arrow::WriteTable(
        *table->Slice(0, 5), arrow::default_memory_pool(), output, 2048
    ));
    ARROW_ASSIGN_OR_RAISE(output, filesystem->OpenOutputStream(base_path + "/data2.parquet"));
    ARROW_RETURN_NOT_OK(parquet::arrow::WriteTable(
        *table->Slice(5), arrow::default_memory_pool(), output, 2048
    ));
    return base_path;
}


arrow::Status PrepareEnv() {
    ARROW_ASSIGN_OR_RAISE(auto src_table, CreateTable());

    std::shared_ptr<arrow::fs::FileSystem> setup_fs;
    char setup_path[256];
    char* result = getcwd(setup_path, 256);
    if(result == nullptr) {
        return arrow::Status::IOError("Fetching PWD failed.");
    }

    ARROW_ASSIGN_OR_RAISE(setup_fs, arrow::fs::FileSystemFromUriOrPath(setup_path));
    ARROW_ASSIGN_OR_RAISE(auto dset_path, CreateExampleParquetDataset(setup_fs, ""));
    
    return arrow::Status::OK();
}

arrow::Status run_main() {
    ARROW_RETURN_NOT_OK(PrepareEnv());
    std::shared_ptr<arrow::fs::FileSystem> fs;
    char init_path[256];
    char* result = getcwd(init_path, 256);

    if(result == nullptr) {
        return arrow::Status::IOError("Fetching PWD failed.");
    }  

    ARROW_ASSIGN_OR_RAISE(fs, arrow::fs::FileSystemFromUriOrPath(init_path));
    arrow::fs::FileSelector selector;
    selector.base_dir = "parquet_dataset";
    selector.recursive = true;
    arrow::dataset::FileSystemFactoryOptions options;
    // We'll use Hive-style partitioning. We'll let Arrow Datasets infer the partition
    // schema. We won't set any other options, defaults are fine.
    options.partitioning = arrow::dataset::HivePartitioning::MakeFactory();
    auto read_format = std::make_shared<arrow::dataset::ParquetFileFormat>();
    ARROW_ASSIGN_OR_RAISE(auto factory, arrow::dataset::FileSystemDatasetFactory::Make(
        fs, selector, read_format, options
    ));

    ARROW_ASSIGN_OR_RAISE(auto read_dataset, factory->Finish());
    ARROW_ASSIGN_OR_RAISE(auto fragments, read_dataset->GetFragments());
    for(auto const& fragment : fragments) {
        std::cout << "Found fragment: " << (*fragment)->ToString() << std::endl;
        std::cout << "Partition expression: "
            << (*fragment)->partition_expression().ToString() << std::endl;
    }

    ARROW_ASSIGN_OR_RAISE(auto read_scan_builder, read_dataset->NewScan());
    ARROW_ASSIGN_OR_RAISE(auto read_scanner, read_scan_builder->Finish());

    ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::Table> table, read_scanner->ToTable());
    std::cout << table->ToString() << std::endl;

    std::shared_ptr<arrow::TableBatchReader> write_dataset = std::make_shared<arrow::TableBatchReader>(table);

    auto write_scanner_builder = arrow::dataset::ScannerBuilder::FromRecordBatchReader(write_dataset);
    ARROW_ASSIGN_OR_RAISE(auto write_scanner, write_scanner_builder->Finish());

    // The partition schema determines which fields are used as keys for partitioning.
    auto partition_schema = arrow::schema({arrow::field("a", arrow::utf8())});

    auto partitioning = std::make_shared<arrow::dataset::HivePartitioning>(partition_schema);
    auto write_format = std::make_shared<arrow::dataset::ParquetFileFormat>();
    arrow::dataset::FileSystemDatasetWriteOptions write_options;
    write_options.file_write_options = write_format->DefaultWriteOptions();
    write_options.filesystem = fs;
    write_options.base_dir = "write_dataset";
    write_options.partitioning = partitioning;
    write_options.basename_template = "part{i}.parquet";
    
    // Set behavior to overwrite existing data -- specifically, this lets this example
    // be run more than once, and allows whatever code you have to overwrite what's there.
    write_options.existing_data_behavior = arrow::dataset::ExistingDataBehavior::kOverwriteOrIgnore;
    ARROW_RETURN_NOT_OK(arrow::dataset::FileSystemDataset::Write(write_options, write_scanner));
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