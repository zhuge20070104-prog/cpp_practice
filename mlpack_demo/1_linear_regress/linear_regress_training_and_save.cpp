#include "mlpack/methods/linear_regression/linear_regression.hpp"
#include "mlpack/core.hpp"

#include <iostream>

using namespace mlpack;

int main(int argc, char* argv[]) {
    arma::mat data;
    arma::mat responses;
    data::Load("./input.csv", data);
    data::Load("./output.csv", responses);
    mlpack::regression::LinearRegression lr(data, responses);
    std::cout << "data: " << data << std::endl;
    std::cout << "response: " <<  responses << std::endl;
    arma::vec parameters = lr.Parameters();
    std::cout << "parameters: " <<  parameters << std::endl;

    data::Save("lr_model.xml", "lr_model", lr, false);
    return EXIT_SUCCESS;
}