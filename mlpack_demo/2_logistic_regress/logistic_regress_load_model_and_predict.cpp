#include "mlpack/methods/logistic_regression/logistic_regression.hpp"
#include "mlpack/core.hpp"

#include <iostream>

using namespace mlpack;

int main(int argc, char* argv[]) {
    std::string filename = "./lr_model.xml";

    regression::LogisticRegression lr;
    data::Load(filename, "lr_model", lr);

    arma::mat predict_in;
    arma::mat predict_resp;
    data::Load("./input.csv", predict_in);

    lr.Classify(predict_in, predict_resp);
    std::cout << "Predict response: "  << predict_resp.row(1) << std::endl;

    return EXIT_SUCCESS;
}