from pyspark.sql import SparkSession
from pyspark.sql import functions as func
from pyspark.sql.types import StructType, StructField, IntegerType, StringType

spark = SparkSession.builder.appName("MostPopularSuperhero").getOrCreate()

schema = StructType([\
    StructField("id", IntegerType(), True),
    StructField("name", StringType(), True),
    ])

names = spark.read.option("sep", " ").schema(schema).csv("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/Marvel+Names")
lines = spark.read.text("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/Marvel+Graph")

connections = lines.withColumn("id", func.split(func.col("value"), " ")[0]) \
    .withColumn("connections", func.size(func.split(func.trim(func.col("value")), " ")) - 1) \
    .groupBy("id").agg(func.sum("connections").alias("connections"))

mostPopular = connections.sort(func.desc("connections")).first()

mostPopularName = names.filter(func.col("id") == mostPopular[0]).select("name").first()

print(mostPopularName[0] + " is the most popular superhero with " + str(mostPopular[1]) + " co-appearances.")

spark.stop()