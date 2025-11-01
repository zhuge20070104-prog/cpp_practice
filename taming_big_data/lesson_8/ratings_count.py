from pyspark import SparkConf, SparkContext

import collections

conf = SparkConf().setMaster("local").setAppName("RatingsHistogram")

sc = SparkContext(conf = conf)

lines = sc.textFile("file:///mnt/c/code/cpp_practice/taming_big_data/datasets/ml-100k/u.data")
ratings = lines.map(lambda x: x.split()[2])

# ['3', '3', '1', '2', '1']  
# print(ratings.take(5))

result = ratings.countByValue()

# defaultdict(<class 'int'>, {'3': 27145, '1': 6110, '2': 11370, '4': 34174, '5': 21201})
# print(result)

# default sort by key
# Sort by value: sortedResults = collections.OrderedDict(sorted(result.items(), key=lambda x: x[1]))
sortedResults = collections.OrderedDict(sorted(result.items()))

for key, value in sortedResults.items():
    print("%s %i" % (key, value))



