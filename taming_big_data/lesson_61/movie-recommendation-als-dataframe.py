from pyspark.sql import SparkSession
from pyspark.sql.types import StructType, StructField, IntegerType, LongType
from pyspark.ml.recommendation import ALS
import sys
import codecs

def loadMovieNames():
    movieNames = {}
    with codecs.open("/mnt/c/code/cpp_practice/taming_big_data/datasets/ml-100k/u.item", "r", encoding="ISO-8859-1", errors="ignore") as f:
        for line in f:
            fields = line.split("|")
            movieNames[int(fields[0])] = fields[1]
    return movieNames


spark = SparkSession.builder.appName("ALSExample").getOrCreate()

moviesSchema = StructType([\
    StructField("userID", IntegerType(), True),
    StructField("movieID", IntegerType(), True),
    StructField("rating", IntegerType(), True),
    StructField("timestamp", LongType(), True),
    ])

names = loadMovieNames()

ratings = spark.read.option("sep", "\t").schema(moviesSchema) \
    .csv("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/ml-100k/u.data")

print("Training Recommendation Model...")

als = ALS().setMaxIter(5).setRegParam(0.01).setUserCol("userID").setItemCol("movieID") \
    .setRatingCol("rating")

model = als.fit(ratings)

userID = int(sys.argv[1])

userSchema = StructType([\
    StructField("userID", IntegerType(), True),
    ])

users = spark.createDataFrame([(userID,)], userSchema)

recommendations = model.recommendForUserSubset(users, 10).collect()

print("\nTop 10 recommendations for user ID " + str(userID) + ":")

for userRecs in recommendations:
    #userRecs is (userID, [Row(movieId, rating), Row(movieID, rating)...])
    myRecs = userRecs[1]
    for rec in myRecs:
        movie = rec[0]
        rating = rec[1]
        movieName = names[movie]
        print(movieName + ":\t" + str(rating))

spark.stop()