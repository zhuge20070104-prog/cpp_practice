#include "gen_data.h"


arrow::Result<std::shared_ptr<arrow::Table>> CreateTable() {
    auto schema = arrow::schema({
        arrow::field("a", arrow::int64()),
        arrow::field("b", arrow::int64()),
        arrow::field("c", arrow::int64())
    });

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
    std::shared_ptr<fs::FileSystem> const& filesystem,
    std::string const& base_path 
) {
    ARROW_RETURN_NOT_OK(filesystem->CreateDir(base_path));
    ARROW_ASSIGN_OR_RAISE(auto table, CreateTable());
    ARROW_ASSIGN_OR_RAISE(auto output, filesystem->OpenOutputStream(base_path+"/data1.parquet"));
    ARROW_RETURN_NOT_OK(parquet::arrow::WriteTable(
        *table->Slice(0, 5), arrow::default_memory_pool(), output, 2048
    ));
    ARROW_ASSIGN_OR_RAISE(output, filesystem->OpenOutputStream(base_path+"/data2.parquet"));
    ARROW_RETURN_NOT_OK(parquet::arrow::WriteTable(
        *table->Slice(5), arrow::default_memory_pool(), output, 2048
    ));
    return base_path;
}

arrow::Result<std::string> CreateExampleParquetHivePartitionedDataset(
    const std::shared_ptr<fs::FileSystem>& filesystem,
    const std::string& base_path) {
    ARROW_RETURN_NOT_OK(filesystem->CreateDir(base_path));
    auto schema = arrow::schema({
        arrow::field("a", arrow::int64()),
        arrow::field("b", arrow::int64()),
        arrow::field("c", arrow::int64()),
        arrow::field("part", arrow::utf8())
    });

    std::vector<std::shared_ptr<arrow::Array>> arrays(4);
    arrow::NumericBuilder<arrow::Int64Type> builder;
    ARROW_RETURN_NOT_OK(builder.AppendValues({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    ARROW_RETURN_NOT_OK(builder.Finish(&arrays[0]));
    builder.Reset();
    ARROW_RETURN_NOT_OK(builder.AppendValues({9, 8, 7, 6, 5, 4, 3, 2, 1, 0}));
    ARROW_RETURN_NOT_OK(builder.Finish(&arrays[1]));
    builder.Reset();
    ARROW_RETURN_NOT_OK(builder.AppendValues({1, 2, 1, 2, 1, 2, 1, 2, 1, 2}));
    ARROW_RETURN_NOT_OK(builder.Finish(&arrays[2]));

    arrow::StringBuilder string_builder;
    ARROW_RETURN_NOT_OK(
      string_builder.AppendValues({"a", "a", "a", "a", "a", "b", "b", "b", "b", "b"}));
    ARROW_RETURN_NOT_OK(string_builder.Finish(&arrays[3]));

    auto table = arrow::Table::Make(schema, arrays);
    auto dataset = std::make_shared<ds::InMemoryDataset>(table);
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, dataset->NewScan());
    ARROW_ASSIGN_OR_RAISE(auto scanner, scan_builder->Finish());

    auto partition_schema = arrow::schema({arrow::field("part", arrow::utf8())});
    auto partitioning = std::make_shared<ds::HivePartitioning>(partition_schema);
    auto format = std::make_shared<ds::ParquetFileFormat>();
    ds::FileSystemDatasetWriteOptions write_options;
    write_options.file_write_options = format->DefaultWriteOptions();
    write_options.filesystem = filesystem;
    write_options.base_dir = base_path;
    write_options.partitioning = partitioning;
    write_options.basename_template = "part{i}.parquet";
    ARROW_RETURN_NOT_OK(ds::FileSystemDataset::Write(write_options, scanner));
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
    ARROW_ASSIGN_OR_RAISE(auto dset_path, CreateExampleParquetDataset(setup_fs, PARQUET_DATASET_PATH));
    ARROW_ASSIGN_OR_RAISE(auto dset_part_path, 
        CreateExampleParquetHivePartitionedDataset(setup_fs, PARQUET_PART_DATASET_PATH));
    
    return arrow::Status::OK();
}


arrow::Result<FileEnv> PrepareFileEnv(DatasetType dset_type) {
    std::shared_ptr<arrow::fs::FileSystem> setup_fs;
    char setup_path[256];
    char* result = getcwd(setup_path, 256);
    if(result == nullptr) {
        return arrow::Status::IOError("Fetching PWD failed.");
    }


    std::shared_ptr<ds::FileFormat> format = std::make_shared<ds::ParquetFileFormat>();
    ARROW_ASSIGN_OR_RAISE(setup_fs, arrow::fs::FileSystemFromUriOrPath(setup_path));
    FileEnv file_env{setup_fs, format, std::string(PARQUET_DATASET_PATH)};
    if(dset_type == Partitioned) {
        file_env.data_set_dir = PARQUET_PART_DATASET_PATH;
    }
    return file_env;
} 