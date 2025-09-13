#ifndef _FREDRIC_FILE_GEN_H_
#define _FREDRIC_FILE_GEN_H_

#include <iostream>
#include <arrow/api.h>
#include <arrow/csv/api.h>
#include <arrow/io/api.h>
#include <arrow/ipc/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>

arrow::Status gen_initial_file();

#endif