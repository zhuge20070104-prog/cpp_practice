from pyspark.sql import SparkSession
from pyspark.sql import functions as func

spark = SparkSession.builder.appName("WordCount").getOrCreate()
inputDF = spark.read.text("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/Book")

words = inputDF.select(func.explode(func.split(inputDF.value, "\\W+")).alias("word"))
wordWithoutEmptyStrings = words.filter(words.word != "")

lowerCaseWords = wordWithoutEmptyStrings.select(func.lower(wordWithoutEmptyStrings.word).alias("word"))
wordCounts = lowerCaseWords.groupBy("word").count()

wordCountsSorted = wordCounts.sort(func.desc("count"))

wordCountsSorted.show(20)

spark.stop()