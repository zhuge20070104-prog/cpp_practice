# Mlpack command line tool

## Install mlpack command line tool,

```shell
    sudo apt-get install mlpack-bin
```

## Logistic regression using command line tool

```shell
    mlpack_logistic_regression  --training_file ./iris.csv -v -M lr.xml
```


## Compute model and predict at the same time

```shell
    mlpack_logistic_regression --training_file iris.csv --test_file input.csv --output_probabilities_file predictions.csv -v
```

## Prediction using a precomputed model

```shell
   mlpack_logistic_regression --input_model_file lr.xml --test_file input.csv --output_probabilities_file  predictions.csv -v
```

