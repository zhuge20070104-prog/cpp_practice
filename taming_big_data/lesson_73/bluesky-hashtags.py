import random
import os
import re
import json

from pyspark.sql import SparkSession
from pyspark.sql.functions import udf, udtf 
from pyspark.sql.types import StringType


LOG_FILE = "/mnt/c/code/cpp_practice/taming_big_data/datasets/bluesky.jsonl"

spark = SparkSession.builder.appName("BlueskyHashtags").getOrCreate()


@udf(StringType())
def get_random_log_line():
    try:
        if not os.path.exists(LOG_FILE):
            return None
        
        file_size = os.path.getsize(LOG_FILE)
        if file_size == 0:
            return None
        
        with open(LOG_FILE, "r") as lf:
            while True:
                random_position = random.randint(0, file_size - 1)
                lf.seek(random_position)
                lf.readline()
                line = lf.readline().strip()
                
                if line:
                    return line
    except Exception as e:
        print(str(e))
        return None
    

@udtf(returnType="hashtag: string")
class HashtagExtractor:
    def eval(self, json_line: str):
        """Extracts hashtags from the input text"""
        try:
            data = json.loads(json_line)
            text = data.get("text", "")
            if text:
                hashtags = re.findall(r'#\w+', text)
                for hashtag in hashtags:
                    yield (hashtag.lower(), )
        except:
            yield None


spark.udtf.register("extract_hashtags", HashtagExtractor)

rate_df = spark.readStream.format("rate") \
    .option("rowsPerSecond", 5).load()

postLines = rate_df.withColumn("json", get_random_log_line())

postLines.createOrReplaceTempView("raw_posts")

hashtags_query = """
SELECT hashtag
    from raw_posts, LATERAL extract_hashtags(json)
"""

hashtagsDF = spark.sql(hashtags_query)

hashtagsDF.createOrReplaceTempView("hashtags")

topHashtagsDF = spark.sql("""
SELECT hashtag, COUNT(*) AS count
    FROM hashtags
    WHERE hashtag IS NOT NULL
    GROUP BY hashtag
    ORDER BY count DESC
    LIMIT 10
""")


query = (topHashtagsDF.writeStream.outputMode("complete").format("console").queryName("top_hashtags").start())

query.awaitTermination()

spark.stop()

