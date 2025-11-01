from pyspark import SparkConf, SparkContext

conf = SparkConf().setMaster("local").setAppName("FriendsByAge")
sc = SparkContext(conf = conf)

def parseLine(line):
    fields = line.split(',')
    age = int(fields[2])
    numFriends = int(fields[3])
    return (age, numFriends)


lines = sc.textFile("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/fakefriends.csv")
'''
Data set format changes -->
# 第13行: lines.map(parseLine)
rdd = [(33, 385), (26, 2), (55, 221), (40, 465), (33, 74), (26, 100)]

# 第14行第一步: mapValues(lambda x: (x, 1))
中间 = [(33, (385,1)), (26, (2,1)), (55, (221,1)), (40, (465,1)), (33, (74,1)), (26, (100,1))]

# 第14行第二步: reduceByKey(...)
totalsByAge = [(33, (459, 2)), (26, (102, 2)), (55, (221, 1)), (40, (465, 1))]

# 第15行: mapValues(lambda x: x[0]/x[1])
averagesByAge = [(33, 229.5), (26, 51.0), (55, 221.0), (40, 465.0)]

# 第16行: collect()
results = [(33, 229.5), (26, 51.0), (55, 221.0), (40, 465.0)]
'''
rdd = lines.map(parseLine)
totalsByAge = rdd.mapValues(lambda x: (x, 1)).reduceByKey(lambda x, y: (x[0] + y[0], x[1] + y[1]))
averagesByAge = totalsByAge.mapValues(lambda x: x[0] / x[1])
results = averagesByAge.collect()
for result in results:
    print(result)