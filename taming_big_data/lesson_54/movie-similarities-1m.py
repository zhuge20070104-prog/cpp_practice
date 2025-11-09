import sys
from pyspark import SparkConf, SparkContext
from math import sqrt

def loadMovieNames():
    movieNames = {}
    with open("/mnt/c/code/cpp_practice/taming_big_data/datasets/ml-1m/movies.dat", encoding="ascii", errors="ignore") as f:
        for line in f:
            fields = line.split("::")
            movieNames[int(fields[0])] = fields[1]
    return movieNames


def makePairs(userRatings):
    ratings = userRatings[1]
    (movie1, rating1) = ratings[0]
    (movie2, rating2) = ratings[1]
    return ((movie1, movie2), (rating1, rating2))

def filterDuplicates(userRatings):
    ratings = userRatings[1]
    (movie1, rating1) = ratings[0]
    (movie2, rating2) = ratings[1]
    return movie1 < movie2


def computeCosineSimilarity(ratingPairs):
    numPairs = 0
    sum_xx = sum_yy = sum_xy = 0
    for ratingX, ratingY in ratingPairs:
        sum_xx += ratingX * ratingX
        sum_yy += ratingY * ratingY
        sum_xy += ratingX * ratingY
        numPairs += 1
    
    numerator = sum_xy
    denominator = sqrt(sum_xx) * sqrt(sum_yy)
    
    score = 0
    if denominator != 0:
        score = (numerator / float(denominator))
    return (score, numPairs)

conf = SparkConf() \
    .setMaster("local[*]") \
    .setAppName("MovieSimilarities") \
    .set("spark.driver.memory", "16g") \
    .set("spark.executor.memory", "16g") \
    .set("spark.sql.shuffle.partitions", "200") \
    .set("spark.default.parallelism", "200") \
    .set("spark.memory.fraction", "0.8") \
    .set("spark.memory.storageFraction", "0.3") \
    .set("spark.shuffle.compress", "true") \
    .set("spark.shuffle.spill.compress", "true") \
    .set("spark.rdd.compress", "true") \
    .set("spark.serializer", "org.apache.spark.serializer.KryoSerializer") \
    .set("spark.kryoserializer.buffer.max", "512m")

sc = SparkContext(conf = conf)

print("\nLoading movie names...")
movieNames = loadMovieNames()

data = sc.textFile("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/ml-1m/ratings.dat")
ratings = data.map(lambda l: l.split("::")).map(lambda l: (int(l[0]), (int(l[1]), float(l[2]))))
ratingsPartitioned = ratings.partitionBy(200)
joinedRatings = ratingsPartitioned.join(ratingsPartitioned)

uniqueJoinedRatings = joinedRatings.filter(filterDuplicates)
moviePairs = uniqueJoinedRatings.map(makePairs).partitionBy(200)

moviePairRatings = moviePairs.groupByKey()

moviePairSimilarities = moviePairRatings.mapValues(computeCosineSimilarity).persist()

moviePairSimilarities.sortByKey()

# moviePairSimilarities.saveAsTextFile("movie-sims")

if len(sys.argv) > 1:
    scoreThreshold = 0.97
    coOccurenceThreshold = 50.0
    movieID = int(sys.argv[1])

    filteredResults = moviePairSimilarities.filter(lambda pairScore: \
        (pairScore[0][0] == movieID or pairScore[0][1] == movieID) \
        and (pairScore[1][0] > scoreThreshold) \
        and (pairScore[1][1] > coOccurenceThreshold))
    
    results = filteredResults.map(lambda pairScore: (pairScore[1], pairScore[0])).sortByKey(ascending=False).take(10)
    print("Top 10 similar movies for " + movieNames[movieID])
    for result in results:
        (sim, pair) = result
        similarMovieID = pair[0]
        if similarMovieID == movieID:
            similarMovieID = pair[1]
        print(movieNames[similarMovieID] + "\tscore: " + str(sim[0]) + "\tstrength: " + str(sim[1]))

