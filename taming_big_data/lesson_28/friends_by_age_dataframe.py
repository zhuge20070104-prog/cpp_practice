from pyspark.sql import SparkSession
from pyspark.sql import Row
from pyspark.sql import functions as func


spark = SparkSession.builder.appName("FriendsByAge").getOrCreate()
lines = spark.read.option("header", "true").option("inferSchema", "true") \
    .csv("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/fakefriends-header.csv")

friendsByAge = lines.select("age", "friends")
friendsByAge.groupBy("age").avg("friends").show()
friendsByAge.groupBy("age").avg("friends").sort("age").show()

friendsByAge.groupBy("age").agg(func.round(func.avg("friends"), 2)).sort("age").show()

'''
agg() 返回的是一个 DataFrame
DataFrame 的 alias() 方法是用来给整个 DataFrame 起别名（通常用在 join 操作中）
要给聚合结果的列起别名，需要在 agg() 的参数内部调用 .alias()
修改后，列名就会显示为 friends_avg 而不是 round(avg(friends), 2) 了。
'''
friendsByAge.groupBy("age").agg(func.round(func.avg("friends"), 2).alias("friends_avg")).sort("age").show()

spark.stop()