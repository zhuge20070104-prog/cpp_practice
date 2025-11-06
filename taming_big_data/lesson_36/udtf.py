from pyspark.sql import SparkSession
from pyspark.sql.functions import udtf, udf
from pyspark.sql.types import IntegerType
import re

# User defined table function
@udtf(returnType="hashtag: string")
class HashtagExtractor:
    def eval(self, text: str):
        """Extracts hashtags from the input text"""
        if text:
            hashtags = re.findall(r'#(\w+)', text)
            for hashtag in hashtags:
                yield (hashtag, )

# User defined function
@udf(returnType=IntegerType())
def count_hashtags(text: str):
    """Counts the number of hashtags in the input text"""
    if text:
        return len(re.findall(r'#(\w+)', text))
    return 0


# Initialize Spark Session
spark = SparkSession.builder. \
    appName("Python UDF and UDTF Example"). \
    config("spark.sql.execution.pythonUDTF.enabled", "true"). \
    getOrCreate()

# Register the UDTF for use in Spark SQL
spark.udtf.register("extract_hashtags", HashtagExtractor)

# Register the UDF for use in Spark SQL
spark.udf.register("count_hashtags", count_hashtags)

# Example: Using the UDTF in SQL
print("\nUDTF Example (Extract Hashtags):")
spark.sql("SELECT * FROM extract_hashtags('Welcome to #ApacheSpark and #BigData!')").show()

# Example: Using the UDF in SQL
print("\nUDF Example (Count Hashtags):")
spark.sql("SELECT count_hashtags('Welcome to #ApacheSpark and #BigData!') AS hashtag_count").show()

# Using Both UDTF and UDF with a DataFrame
data = [("Learning #AI with #ML",), ("Explore #DataScience", ), ("No hashtags here", )]
df = spark.createDataFrame(data, ["text"])

# Apply UDF in a DataFrame query
df.selectExpr("text", "count_hashtags(text) AS hashtag_count").show()

'''
完整的执行流程：
tweets 表有一列 text，包含推文内容
LATERAL extract_hashtags(text) 对每条推文调用函数
UDTF 从文本中提取所有 hashtag，每个 hashtag 生成一行
每行包含 hashtag 列（由 returnType 定义）
最终结果将原始的 text 列和提取出的 hashtag 列组合在一起
从输出结果可以看到，一行输入可以产生多行输出：
'''

# Apply UDTF with a LATERAL JOIN
print("\nUsing UDTF with LATERAL JOIN:")
df.createOrReplaceTempView("tweets")
spark.sql("SELECT text, hashtag FROM tweets, LATERAL extract_hashtags(text)").show()

spark.stop()