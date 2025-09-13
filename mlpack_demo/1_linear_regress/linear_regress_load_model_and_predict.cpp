#include "mlpack/methods/linear_regression/linear_regression.hpp"
#include "mlpack/core.hpp"

#include <iostream>

using namespace mlpack;

int main(int argc, char* argv[]) {
    std::string filename = "./lr_model.xml";

    regression::LinearRegression lr;
    data::Load(filename, "lr_model", lr);

    arma::mat predict_in;
    arma::rowvec predict_resp;
    data::Load("./predict.csv", predict_in);

    lr.Predict(predict_in, predict_resp);
    std::cout << "Predict response: "  << predict_resp << std::endl;

    return EXIT_SUCCESS;
}