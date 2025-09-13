#include "mlpack/methods/logistic_regression/logistic_regression.hpp"
#include "mlpack/core.hpp"
#include "cls_split_data.h"

#include <iostream>

using namespace mlpack;

int main(int argc, char* argv[]) {
    InputType data;
    ClsResponseType resp;
    data::Load("./iris.csv", data);
    cls_split_data(data, resp);

    mlpack::regression::LogisticRegression lr(data, resp);
    std::cout << "data: " << data << std::endl;
    std::cout << "response: " <<  resp << std::endl;
    arma::mat parameters = lr.Parameters();
    std::cout << "parameters: " <<  parameters << std::endl;

    data::Save("lr_model.xml", "lr_model", lr, true);
    return EXIT_SUCCESS;
}