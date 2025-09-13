#ifndef _FREDRIC_CLS_SPLIT_DATA_H_
#define _FREDRIC_CLS_SPLIT_DATA_H_
#include "mlpack/core.hpp"

using InputType = arma::mat;
using ClsResponseType = arma::Row<std::size_t>;

void cls_split_data(arma::mat& data, arma::Row<std::size_t>& resp);
#endif