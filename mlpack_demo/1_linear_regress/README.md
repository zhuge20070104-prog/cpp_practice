# Mlpack command line tool

## Install mlpack command line tool,

```shell
    sudo apt-get install mlpack-bin
```

## Linear regression using command line tool

```shell
    mlpack_linear_regression --training_file dataset.csv -v -M lr.xml
```

## Training a multivariable linear regression model

```shell
    mlpack_linear_regression --training_file dataset_2.csv -v -M lr2.xml
```

## Compute model and predict at the same time

```shell
    mlpack_linear_regression --training_file dataset.csv --test_file predict.csv --output_predictions_file predictions.csv -v
```

## Prediction using a precomputed model

```shell
    mlpack_linear_regression --input_model_file lr.xml --test_file predict.csv --output_predictions_file predictions1.csv -v
```

