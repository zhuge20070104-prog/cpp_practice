#include "cls_split_data.h"

void cls_split_data(arma::mat& data, arma::Row<std::size_t>& resp) {
    // Get a copy of the original data
    auto data_cp = data;
    
    auto cols= data.n_cols;
    auto rows = data.n_rows;
    // Get rid of the last actual value row
    data.resize(arma::SizeMat{rows-1, cols});
    // Get the last actual value row as double
    auto resp_dbl = data_cp.row(rows-1);
    // Convert the double value row to std::size_t 1 by 1
    resp.resize(arma::SizeMat{1, resp_dbl.n_elem});
    resp.reshape(1, resp_dbl.n_elem);
    int i = 0;
    for(auto ele: resp_dbl) {
        resp.at(0, i) = (std::size_t)ele;
        ++i;
    }
}