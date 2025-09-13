#ifndef _FREDRIC_GEN_DATA_H_
#define _FREDRIC_GEN_DATA_H_

#include <arrow/api.h>
#include <arrow/compute/api.h>
#include <iostream>

arrow::Result<std::shared_ptr<arrow::Table>> gen_data();

#endif