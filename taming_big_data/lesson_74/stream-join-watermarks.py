import random
from pyspark.sql import SparkSession
from pyspark.sql.functions import col, expr, udf
from pyspark.sql.types import StringType


spark = SparkSession.builder.appName("StreamJoinWatermarks").getOrCreate()

USER_IDS = ["user_001", "user_002", "user_003", "user_004", "user_005"]
TRANSACTION_IDS = ["123", "456", "789", "987", "654", "321"]
TRANSACTION_STATUSES = ["Approved", "Rejected", "Pending"]


def generate_user_id():
    return random.choice(USER_IDS)

def generate_transaction_id():
    return random.choice(TRANSACTION_IDS)

def generate_transaction_status():
    return random.choice(TRANSACTION_STATUSES)

# Register UDFs
generate_user_id_udf = udf(generate_user_id, StringType())
generate_transaction_id_udf = udf(generate_transaction_id, StringType())
generate_transaction_status_udf = udf(generate_transaction_status, StringType())

transactions_stream = spark.readStream.format("rate") \
    .option("rowsPerSecond", 5) \
    .load() \
    .selectExpr("timestamp AS event_time") \
    .withColumn("user_id", generate_user_id_udf()) \
    .withColumn("transaction_id", generate_transaction_id_udf())

status_stream = spark.readStream.format("rate") \
    .option("rowsPerSecond", 5) \
    .load() \
    .selectExpr("timestamp AS event_time") \
    .withColumn("transaction_id", generate_transaction_id_udf()) \
    .withColumn("status", generate_transaction_status_udf())


transactions_stream = transactions_stream.withWatermark("event_time", "10 seconds")
status_stream = status_stream.withWatermark("event_time", "10 seconds")

joined_stream = transactions_stream.alias("t").join(
    status_stream.alias("s"),
    (col("t.transaction_id") == col("s.transaction_id")) & 
    (col("t.event_time").between(col("s.event_time") - expr("interval 5 seconds"), 
        col("s.event_time") + expr("interval 5 seconds"))),
    "inner"
).select(
    col("t.user_id"),
    col("t.transaction_id"),
    col("s.status"),
    col("t.event_time").alias("transaction_time"),
    col("s.event_time").alias("status_update_time")
)

query = (joined_stream.writeStream.outputMode("append") \
    .format("console") \
    .option("truncate", "false") \
    .queryName("joined_stream") \
    .start())

query.awaitTermination()

spark.stop()


