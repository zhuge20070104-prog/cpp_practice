#ifndef _FREDRIC_GEN_DATA_H_
#define _FREDRIC_GEN_DATA_H_

#include <unistd.h>
#include <arrow/api.h>
#include <arrow/compute/cast.h>
#include <arrow/dataset/dataset.h>
#include <arrow/dataset/discovery.h>
#include <arrow/dataset/file_base.h>
#include <arrow/dataset/file_ipc.h>
#include <arrow/dataset/file_parquet.h>
#include <arrow/dataset/scanner.h>
#include <arrow/filesystem/filesystem.h>
#include <arrow/ipc/writer.h>
#include <arrow/util/iterator.h>
#include <parquet/arrow/writer.h>
#include "arrow/compute/expression.h"

#include <iostream>
#include <vector>

namespace ds = arrow::dataset;
namespace fs = arrow::fs;
namespace cp = arrow::compute;


std::string const PARQUET_DATASET_PATH = "parquet_dataset";
std::string const PARQUET_PART_DATASET_PATH = "parquet_part_dataset";


enum DatasetType {
    Normal,
    Partitioned
};

struct FileEnv {
    std::shared_ptr<fs::FileSystem> fs;
    std::shared_ptr<ds::FileFormat> format;
    std::string data_set_dir;
};

arrow::Result<std::shared_ptr<arrow::Table>> CreateTable();

arrow::Result<std::string> CreateExampleParquetDataset(
    std::shared_ptr<fs::FileSystem> const& filesystem,
    std::string const& base_path 
);

arrow::Result<std::string> CreateExampleParquetHivePartitionedDataset(
    const std::shared_ptr<fs::FileSystem>& filesystem,
    const std::string& base_path);

arrow::Status PrepareEnv();

arrow::Result<FileEnv> PrepareFileEnv(DatasetType dset_type);

#endif