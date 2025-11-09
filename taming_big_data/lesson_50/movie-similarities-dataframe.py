from pyspark.sql import SparkSession
from pyspark.sql import functions as func
from pyspark.sql.types import StructType, StructField, StringType, IntegerType, LongType
import sys

'''
让我详细解释一下这个 .groupBy("movie1", "movie2") 的原因：
数据流程分析
第一步：创建电影对（moviePairs）
在第73-79行，代码通过自连接创建了电影对：
movie-similarities-dataframe.pyLines 73-79
moviePairs = ratings.alias("ratings1") \      
.join(ratings.alias("ratings2"), (func.col("ratings1.userId") == func.col("ratings2.userId")) \            
& (func.col("ratings1.movieId") < func.col("ratings2.movieId"))) \      
.select(func.col("ratings1.movieId").alias("movie1"), \        
func.col("ratings2.movieId").alias("movie2"), \        
func.col("ratings1.rating").alias("rating1"), \        
func.col("ratings2.rating").alias("rating2"))


这会产生类似这样的数据：
userId	movie1	movie2	rating1	rating2
用户A	电影1	电影2	4	5
用户B	电影1	电影2	3	4
用户C	电影1	电影2	5	5
...	...	...	...	...
第二步：为什么需要 groupBy？
正如您所说，多个不同的用户可能都看过并评价了同样的 movie1 和 movie2。所以：

calculateSimilarity = pairScores \
      .groupBy("movie1", "movie2") \
      .agg( \
        func.sum(func.col("xy")).alias("numerator"), \
        (func.sqrt(func.sum(func.col("xx"))) * func.sqrt(func.sum(func.col("yy")))).alias("denominator"), \
        func.count(func.col("xy")).alias("numPairs")
      )

汇总所有用户对同一对电影的评分数据
计算余弦相似度需要的累加值（∑xy, ∑x², ∑y²）
统计有多少用户同时评价了这两部电影（numPairs）
这样才能得到基于所有共同评价用户的电影相似度，而不是单个用户的评价！
'''


def computeCosineSimilarity(spark, data):
    # compute xx, xy and yy columns
    pairScores = data \
        .withColumn("xx", func.col("rating1") * func.col("rating1")) \
        .withColumn("yy", func.col("rating2") * func.col("rating2")) \
        .withColumn("xy", func.col("rating1") * func.col("rating2"))
    
    # compute numerator, denominator and numPairs columns
    calculateSimilarity = pairScores \
        .groupBy("movie1", "movie2") \
        .agg( \
            func.sum(func.col("xy")).alias("numerator"), \
            (func.sqrt(func.sum(func.col("xx"))) * func.sqrt(func.sum(func.col("yy")))).alias("denominator"), \
            func.count(func.col("xy")).alias("numPairs")
        )
    # calculate score and select only needed columns (movie1, movie2, score, numPairs)
    result = calculateSimilarity \
        .withColumn("score", \
            func.when(func.col("denominator") != 0, func.col("numerator") / func.col("denominator")) \
            .otherwise(0.0)) \
        .select("movie1", "movie2", "score", "numPairs")
    return result


# Get movie name by given movieID
def getMovieName(movieNames, movieId):
    result = movieNames.filter(func.col("movieID") == movieId) \
        .select("movieTitle").collect()[0]
    return result[0]


spark = SparkSession.builder.remote("sc://localhost:15002").appName("MovieSimilarities").getOrCreate()

movieNamesSchema = StructType([\
    StructField("movieID", IntegerType(), True),
    StructField("movieTitle", StringType(), True),
    ])

movieSchema = StructType([\
    StructField("userID", IntegerType(), True),
    StructField("movieID", IntegerType(), True),
    StructField("rating", IntegerType(), True),
    StructField("timestamp", LongType(), True),
    ])

movieNames = spark.read \
    .option("sep", "|") \
    .option("charset", "ISO-8859-1") \
    .schema(movieNamesSchema) \
    .csv("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/ml-100k/u.item")

movies = spark.read \
    .option("sep", "\t") \
    .schema(movieSchema) \
    .csv("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/ml-100k/u.data")

ratings = movies.select("userId", "movieId", "rating")

moviePairs = ratings.alias("ratings1") \
    .join(ratings.alias("ratings2"), (func.col("ratings1.userId") == func.col("ratings2.userId")) \
        & (func.col("ratings1.movieId") < func.col("ratings2.movieId"))) \
    .select(func.col("ratings1.movieId").alias("movie1"), \
            func.col("ratings2.movieId").alias("movie2"), \
            func.col("ratings1.rating").alias("rating1"), \
            func.col("ratings2.rating").alias("rating2"))


moviePairSimilarities = computeCosineSimilarity(spark, moviePairs).cache()

if (len(sys.argv) > 1):
    scoreThreshold = 0.97
    coOccurenceThreshold = 50.0

    movieID = int(sys.argv[1])

    filteredResults = moviePairSimilarities.filter( \
        ((func.col("movie1") == movieID) | (func.col("movie2") == movieID)) \
        & (func.col("score") > scoreThreshold) \
        & (func.col("numPairs") > coOccurenceThreshold))
    

    results = filteredResults.sort(func.desc("score")).take(10)

    print("Top 10 similar movies for " + getMovieName(movieNames, movieID))
    for result in results:
        similarMovieID = result.movie1
        if (similarMovieID == movieID):
            similarMovieID = result.movie2
        
        print(getMovieName(movieNames, similarMovieID) + "\tscore: " + str(result.score) + "\tstrength: " + str(result.numPairs))

spark.stop()