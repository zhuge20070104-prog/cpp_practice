from pyspark.sql import SparkSession

import os
os.environ['PYARROW_IGNORE_TIMEZONE'] = '1'

# import pandas on spark
import pyspark.pandas as ps

spark = SparkSession.builder \
    .appName("Pandas API on Spark") \
    .config("spark.sql.ansi.enabled", "false") \
    .config("spark.executorEnv.PYARROW_IGNORE_TIMEZONE", "1") \
    .getOrCreate()

# 1. Create a pandas-on-Spark DataFrame
ps_df = ps.DataFrame({
    "id": [1, 2, 3, 4, 5],
    "name": ["Alice", "Bob", "Charlie", "David", "Emma"],
    "age": [25, 30, 35, 40, 45],
    "salary": [50000, 60000, 75000, 80000, 120000]
})

print("Pandas-on-Spark DataFrame:")
print(ps_df)

# 2. Perform pandas style operations on Spark
print("\nAverage age: ", ps_df["age"].mean())

# Compute summary statistics
print("\nSummary statistics:")
print(ps_df.describe())

# 3. Apply a function, Add a new column with salary increment
ps_df["salary_after_increment"] = ps_df["salary"] * 1.1
print("\nDataFrame after salary increment:")
print(ps_df)

# 4. Filtering (Similar to Pandas)
filtered_ps_df = ps_df[ps_df["age"] > 30]
print("\nFiltered DataFrame (age > 30):")
print(filtered_ps_df)


# 5. Convert Pandas-on-Spark Dataframe to spark Dataframe
spark_df = ps_df.to_spark()
print("\nConverted Spark DataFrame:")
spark_df.show()


# 6. Convert Spark DataFrame back to Pandas-on-Spark DataFrame
ps_df_from_spark = ps.DataFrame(spark_df)
print("\nPandas-on-Spark DataFrame from Spark:")
print(ps_df_from_spark)

spark.stop()