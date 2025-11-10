from pyspark.ml.regression import DecisionTreeRegressor
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler


if __name__ == "__main__":
    spark = SparkSession.builder.appName("DecisionTree").getOrCreate()
    data = spark.read.option("header", True) \
        .option("inferSchema", True) \
        .csv("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/realestate.csv")
    
    assembler = VectorAssembler(inputCols=["HouseAge","DistanceToMRT","NumberConvenienceStores"],
        outputCol="features")
    df = assembler.transform(data).select("PriceOfUnitArea", "features")

    trainTest = df.randomSplit([0.5, 0.5])
    trainingDF = trainTest[0]
    testDF = trainTest[1]

    dtr = DecisionTreeRegressor().setFeaturesCol("features").setLabelCol("PriceOfUnitArea")
    model = dtr.fit(trainingDF)

    fullPredictions = model.transform(testDF).cache()

    predictions = fullPredictions.select("prediction").rdd.map(lambda x: x[0])
    labels = fullPredictions.select("PriceOfUnitArea").rdd.map(lambda x: x[0])

    predictionAndLabel = predictions.zip(labels).collect()

    for prediction in predictionAndLabel:
        print(prediction)
    
    spark.stop()